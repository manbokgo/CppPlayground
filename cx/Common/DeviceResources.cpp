#include "pch.h"
#include "DeviceResources.h"
#include "DirectXHelper.h"

using namespace D2D1;
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml::Controls;
using namespace Platform;

namespace DisplayMetrics
{
	// 고해상도 디스플레이는 렌더링하는 데 많은 GPU 및 배터리 전원이 필요할 수 있습니다.
	// 예를 들어 고해상도 휴대폰의 게임에서 고화질로 초당 60프레임을 렌더링하려는
	// 경우 짧은 배터리 수명으로 인해 문제가 발생할 수 있습니다.
	// 모든 플랫폼 및 폼 팩터에서 고화질로 렌더링하는 결정은
	// 신중하게 내려야 합니다.
	static const bool SupportHighResolutions = false;

	// “고해상도” 디스플레이를 정의하는 기본 임계값입니다. 임계값을 초과하거나
	// SupportHighResolutions가 false인 경우 크기가 50%로
	//줄어듭니다.
	static const float DpiThreshold = 192.0f;		// 표준 데스크톱 디스플레이의 200%입니다.
	static const float WidthThreshold = 1920.0f;	// 너비가 1080p입니다.
	static const float HeightThreshold = 1080.0f;	// 높이가 1080p입니다.
};

// 화면 회전을 계산하는 데 사용되는 상수입니다.
namespace ScreenRotation
{
	// 0도 Z 회전
	static const XMFLOAT4X4 Rotation0(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);

	// 90도 Z 회전
	static const XMFLOAT4X4 Rotation90(
		0.0f, 1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);

	// 180도 Z 회전
	static const XMFLOAT4X4 Rotation180(
		-1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);

	// 270도 Z 회전
	static const XMFLOAT4X4 Rotation270(
		0.0f, -1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);
};

// DeviceResources의 생성자입니다.
DX::DeviceResources::DeviceResources() :
	m_screenViewport(),
	m_d3dFeatureLevel(D3D_FEATURE_LEVEL_9_1),
	m_d3dRenderTargetSize(),
	m_outputSize(),
	m_logicalSize(),
	m_nativeOrientation(DisplayOrientations::None),
	m_currentOrientation(DisplayOrientations::None),
	m_dpi(-1.0f),
	m_effectiveDpi(-1.0f),
	m_deviceNotify(nullptr)
{
	CreateDeviceIndependentResources();
	CreateDeviceResources();
}

// Direct3D 디바이스에 종속되지 않은 리소스를 구성합니다.
void DX::DeviceResources::CreateDeviceIndependentResources()
{
	// Direct2D 리소스를 초기화합니다.
	D2D1_FACTORY_OPTIONS options;
	ZeroMemory(&options, sizeof(D2D1_FACTORY_OPTIONS));

#if defined(_DEBUG)
	// 프로젝트가 디버그 빌드 중인 경우 SDK 레이어를 통해 Direct2D 디버깅을 사용합니다.
	options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif

	// Direct2D 팩터리를 초기화합니다.
	DX::ThrowIfFailed(
		D2D1CreateFactory(
			D2D1_FACTORY_TYPE_SINGLE_THREADED,
			__uuidof(ID2D1Factory3),
			&options,
			&m_d2dFactory
			)
		);

	// DirectWrite 팩터리를 초기화합니다.
	DX::ThrowIfFailed(
		DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory3),
			&m_dwriteFactory
			)
		);

	// WIC(Windows Imaging Component) 팩터리를 초기화합니다.
	DX::ThrowIfFailed(
		CoCreateInstance(
			CLSID_WICImagingFactory2,
			nullptr,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&m_wicFactory)
			)
		);
}

// Direct3D 디바이스를 구성하고 해당 디바이스에 대한 핸들 및 디바이스 컨텍스트를 저장합니다.
void DX::DeviceResources::CreateDeviceResources() 
{
	// 이 플래그는 API 기본값과 다른 색 채널 순서의 표면에 대한 지원을
	// 추가합니다. Direct2D와의 호환성을 위해 필요합니다.
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)
	if (DX::SdkLayersAvailable())
	{
		// 프로젝트가 디버그 빌드 중인 경우에는 이 플래그가 있는 SDK 레이어를 통해 디버깅을 사용하십시오.
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
	}
#endif

	// 이 배열은 이 응용 프로그램에서 지원하는 DirectX 하드웨어 기능 수준 집합을 정의합니다.
	// 순서를 유지해야 합니다.
	// 설명에서 애플리케이션에 필요한 최소 기능 수준을 선언해야 합니다.
	// 별도로 지정하지 않은 경우 모든 애플리케이션은 9.1을 지원하는 것으로 간주됩니다.
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	// Direct3D 11 API 디바이스 개체와 해당 컨텍스트를 만듭니다.
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;

	HRESULT hr = D3D11CreateDevice(
		nullptr,					// 기본 어댑터를 사용하려면 nullptr을 지정합니다.
		D3D_DRIVER_TYPE_HARDWARE,	// 하드웨어 그래픽 드라이버를 사용하여 디바이스를 만듭니다.
		0,							// 드라이버가 D3D_DRIVER_TYPE_SOFTWARE가 아닌 경우 0이어야 합니다.
		creationFlags,				// 디버그 및 Direct2D 호환성 플래그를 설정합니다.
		featureLevels,				// 이 응용 프로그램이 지원할 수 있는 기능 수준 목록입니다.
		ARRAYSIZE(featureLevels),	// 위 목록의 크기입니다.
		D3D11_SDK_VERSION,			// Microsoft Store 앱의 경우 항상 이 값을 D3D11_SDK_VERSION으로 설정합니다.
		&device,					// 만들어진 Direct3D 디바이스를 반환합니다.
		&m_d3dFeatureLevel,			// 만들어진 디바이스의 기능 수준을 반환합니다.
		&context					// 디바이스 직접 컨텍스트를 반환합니다.
		);

	if (FAILED(hr))
	{
		// 초기화에 실패하면 WARP 디바이스로 대체됩니다.
		// WARP에 대한 자세한 내용은 다음을 참조하세요. 
		// https://go.microsoft.com/fwlink/?LinkId=286690
		DX::ThrowIfFailed(
			D3D11CreateDevice(
				nullptr,
				D3D_DRIVER_TYPE_WARP, // 하드웨어 디바이스 대신 WARP 디바이스를 만듭니다.
				0,
				creationFlags,
				featureLevels,
				ARRAYSIZE(featureLevels),
				D3D11_SDK_VERSION,
				&device,
				&m_d3dFeatureLevel,
				&context
				)
			);
	}

	// Direct3D 11.3 API 디바이스 및 직접 컨텍스트에 대한 포인터를 저장합니다.
	DX::ThrowIfFailed(
		device.As(&m_d3dDevice)
		);

	DX::ThrowIfFailed(
		context.As(&m_d3dContext)
		);

	// Direct2D 디바이스 개체 및 해당 컨텍스트를 만듭니다.
	ComPtr<IDXGIDevice3> dxgiDevice;
	DX::ThrowIfFailed(
		m_d3dDevice.As(&dxgiDevice)
		);

	DX::ThrowIfFailed(
		m_d2dFactory->CreateDevice(dxgiDevice.Get(), &m_d2dDevice)
		);

	DX::ThrowIfFailed(
		m_d2dDevice->CreateDeviceContext(
			D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
			&m_d2dContext
			)
		);
}

// 창 크기가 변경될 때마다 이러한 리소스를 다시 만들어야 합니다.
void DX::DeviceResources::CreateWindowSizeDependentResources() 
{
	// 이전 창 크기와 관련된 컨텍스트를 지웁니다.
	ID3D11RenderTargetView* nullViews[] = {nullptr};
	m_d3dContext->OMSetRenderTargets(ARRAYSIZE(nullViews), nullViews, nullptr);
	m_d3dRenderTargetView = nullptr;
	m_d2dContext->SetTarget(nullptr);
	m_d2dTargetBitmap = nullptr;
	m_d3dDepthStencilView = nullptr;
	m_d3dContext->Flush1(D3D11_CONTEXT_TYPE_ALL, nullptr);

	UpdateRenderTargetSize();

	// 스왑 체인의 너비와 높이는 창의 가로 방향 너비 및 높이를
	// 기준으로 해야 합니다. 창이 기준 방향이 아닌 경우에는
	// 치수를 반대로 해야 합니다.
	DXGI_MODE_ROTATION displayRotation = ComputeDisplayRotation();

	bool swapDimensions = displayRotation == DXGI_MODE_ROTATION_ROTATE90 || displayRotation == DXGI_MODE_ROTATION_ROTATE270;
	m_d3dRenderTargetSize.Width = swapDimensions ? m_outputSize.Height : m_outputSize.Width;
	m_d3dRenderTargetSize.Height = swapDimensions ? m_outputSize.Width : m_outputSize.Height;

	if (m_swapChain != nullptr)
	{
		// 스왑 체인이 이미 존재할 경우 크기를 조정합니다.
		HRESULT hr = m_swapChain->ResizeBuffers(
			2, // 이중 버퍼링된 스왑 체인입니다.
			lround(m_d3dRenderTargetSize.Width),
			lround(m_d3dRenderTargetSize.Height),
			DXGI_FORMAT_B8G8R8A8_UNORM,
			0
			);

		if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
		{
			// 어떤 이유로든 디바이스가 제거된 경우 새 디바이스와 스왑 체인을 만들어야 합니다.
			HandleDeviceLost();

			// 이제 설정이 완료되었습니다. 이 메서드를 계속 실행하지 않습니다. HandleDeviceLost는 이 메서드를 다시 입력하고 
			// 새 디바이스를 올바르게 설정합니다.
			return;
		}
		else
		{
			DX::ThrowIfFailed(hr);
		}
	}
	else
	{
		// 그렇지 않으면 기존 Direct3D 디바이스와 동일한 어댑터를 사용하여 새 항목을 만듭니다.
		DXGI_SCALING scaling = DisplayMetrics::SupportHighResolutions ? DXGI_SCALING_NONE : DXGI_SCALING_STRETCH;
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {0};

		swapChainDesc.Width = lround(m_d3dRenderTargetSize.Width);		// 창의 크기를 맞춥니다.
		swapChainDesc.Height = lround(m_d3dRenderTargetSize.Height);
		swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;				// 가장 일반적인 스왑 체인 형식입니다.
		swapChainDesc.Stereo = false;
		swapChainDesc.SampleDesc.Count = 1;								// 다중 샘플링을 사용하지 마십시오.
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2;									// 이중 버퍼링을 사용하여 대기 시간을 최소화합니다.
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;	// 모든 Microsoft Store 앱은 이 SwapEffect를 사용해야 합니다.
		swapChainDesc.Flags = 0;
		swapChainDesc.Scaling = scaling;
		swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;

		// 이 시퀀스는 위에서 Direct3D 디바이스를 만드는 데 사용된 DXGI 팩터리를 가져옵니다.
		ComPtr<IDXGIDevice3> dxgiDevice;
		DX::ThrowIfFailed(
			m_d3dDevice.As(&dxgiDevice)
			);

		ComPtr<IDXGIAdapter> dxgiAdapter;
		DX::ThrowIfFailed(
			dxgiDevice->GetAdapter(&dxgiAdapter)
			);

		ComPtr<IDXGIFactory4> dxgiFactory;
		DX::ThrowIfFailed(
			dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory))
			);

		ComPtr<IDXGISwapChain1> swapChain;
		DX::ThrowIfFailed(
			dxgiFactory->CreateSwapChainForCoreWindow(
				m_d3dDevice.Get(),
				reinterpret_cast<IUnknown*>(m_window.Get()),
				&swapChainDesc,
				nullptr,
				&swapChain
				)
			);
		DX::ThrowIfFailed(
			swapChain.As(&m_swapChain)
			);

		// DXGI가 한 번에 두 개 이상의 프레임을 큐에 대기시키지 않도록 합니다. 이렇게 하면 대기 시간이 줄어들고
		// 애플리케이션이 각 VSync 후에만 렌더링되어 전력 소비가 최소화됩니다.
		DX::ThrowIfFailed(
			dxgiDevice->SetMaximumFrameLatency(1)
			);
	}

	// 스왑 체인의 적절한 방향을 설정하고 회전된 스왑 체인으로 렌더링하기 위한
	// 2D 및 3D 매트릭스 변환을 생성합니다.
	// 2D 및 3D 변환의 회전 각도는 서로 다릅니다.
	// 이는 좌표 공간이 서로 달라서 그렇습니다.  또한
	// 3D 매트릭스는 반올림 오류를 방지하기 위해 명시적으로 지정됩니다.

	switch (displayRotation)
	{
	case DXGI_MODE_ROTATION_IDENTITY:
		m_orientationTransform2D = Matrix3x2F::Identity();
		m_orientationTransform3D = ScreenRotation::Rotation0;
		break;

	case DXGI_MODE_ROTATION_ROTATE90:
		m_orientationTransform2D = 
			Matrix3x2F::Rotation(90.0f) *
			Matrix3x2F::Translation(m_logicalSize.Height, 0.0f);
		m_orientationTransform3D = ScreenRotation::Rotation270;
		break;

	case DXGI_MODE_ROTATION_ROTATE180:
		m_orientationTransform2D = 
			Matrix3x2F::Rotation(180.0f) *
			Matrix3x2F::Translation(m_logicalSize.Width, m_logicalSize.Height);
		m_orientationTransform3D = ScreenRotation::Rotation180;
		break;

	case DXGI_MODE_ROTATION_ROTATE270:
		m_orientationTransform2D = 
			Matrix3x2F::Rotation(270.0f) *
			Matrix3x2F::Translation(0.0f, m_logicalSize.Width);
		m_orientationTransform3D = ScreenRotation::Rotation90;
		break;

	default:
		throw ref new FailureException();
	}

	DX::ThrowIfFailed(
		m_swapChain->SetRotation(displayRotation)
		);

	// 스왑 체인 백 버퍼의 렌더링 대상 뷰를 만듭니다.
	ComPtr<ID3D11Texture2D1> backBuffer;
	DX::ThrowIfFailed(
		m_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer))
		);

	DX::ThrowIfFailed(
		m_d3dDevice->CreateRenderTargetView1(
			backBuffer.Get(),
			nullptr,
			&m_d3dRenderTargetView
			)
		);

	// 필요한 경우 3D 렌더링에 사용할 깊이 스텐실 뷰를 만듭니다.
	CD3D11_TEXTURE2D_DESC1 depthStencilDesc(
		DXGI_FORMAT_D24_UNORM_S8_UINT, 
		lround(m_d3dRenderTargetSize.Width),
		lround(m_d3dRenderTargetSize.Height),
		1, // 이 깊이 스텐실 뷰는 하나의 질감만 가지고 있습니다.
		1, // 단일 MIP 맵 수준을 사용합니다.
		D3D11_BIND_DEPTH_STENCIL
		);

	ComPtr<ID3D11Texture2D1> depthStencil;
	DX::ThrowIfFailed(
		m_d3dDevice->CreateTexture2D1(
			&depthStencilDesc,
			nullptr,
			&depthStencil
			)
		);

	CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
	DX::ThrowIfFailed(
		m_d3dDevice->CreateDepthStencilView(
			depthStencil.Get(),
			&depthStencilViewDesc,
			&m_d3dDepthStencilView
			)
		);
	
	// 전체 창을 대상으로 하기 위한 3D 렌더링 뷰포트를 설정합니다.
	m_screenViewport = CD3D11_VIEWPORT(
		0.0f,
		0.0f,
		m_d3dRenderTargetSize.Width,
		m_d3dRenderTargetSize.Height
		);

	m_d3dContext->RSSetViewports(1, &m_screenViewport);

	// 스왑 체인 백 버퍼에 연결된 Direct2D 대상
	// 비트맵을 만들고 이를 현재 대상으로 설정합니다.
	D2D1_BITMAP_PROPERTIES1 bitmapProperties = 
		D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
			m_dpi,
			m_dpi
			);

	ComPtr<IDXGISurface2> dxgiBackBuffer;
	DX::ThrowIfFailed(
		m_swapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer))
		);

	DX::ThrowIfFailed(
		m_d2dContext->CreateBitmapFromDxgiSurface(
			dxgiBackBuffer.Get(),
			&bitmapProperties,
			&m_d2dTargetBitmap
			)
		);

	m_d2dContext->SetTarget(m_d2dTargetBitmap.Get());
	m_d2dContext->SetDpi(m_effectiveDpi, m_effectiveDpi);

	// 모든 Microsoft Store 앱에 회색조 텍스트 앤티앨리어싱을 사용하는 것이 좋습니다.
	m_d2dContext->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
}

// 렌더링 대상의 크기와 렌더링 대상이 축소될지 여부를 결정합니다.
void DX::DeviceResources::UpdateRenderTargetSize()
{
	m_effectiveDpi = m_dpi;

	// 고해상도 디바이스에서 배터리 수명을 개선하려면 더 작은 렌더링 대상으로 렌더링하고
	// 출력이 표현될 때 GPU에서 출력의 크기를 조정할 수 있도록 허용합니다.
	if (!DisplayMetrics::SupportHighResolutions && m_dpi > DisplayMetrics::DpiThreshold)
	{
		float width = DX::ConvertDipsToPixels(m_logicalSize.Width, m_dpi);
		float height = DX::ConvertDipsToPixels(m_logicalSize.Height, m_dpi);

		// 디바이스가 세로 방향이면 높이가 너비보다 큽니다. 큰 치수는
		// 너비 임계값과 비교하고 작은 치수는
		// 높이 임계값과 비교합니다.
		if (max(width, height) > DisplayMetrics::WidthThreshold && min(width, height) > DisplayMetrics::HeightThreshold)
		{
			// 앱의 크기를 조정하기 위해 유효 DPI를 변경합니다. 논리 크기는 변경되지 않습니다.
			m_effectiveDpi /= 2.0f;
		}
	}

	// 필요한 렌더링 대상 크기를 픽셀 단위로 계산합니다.
	m_outputSize.Width = DX::ConvertDipsToPixels(m_logicalSize.Width, m_effectiveDpi);
	m_outputSize.Height = DX::ConvertDipsToPixels(m_logicalSize.Height, m_effectiveDpi);

	// DirectX 콘텐츠 크기를 0으로 만들지 않습니다.
	m_outputSize.Width = max(m_outputSize.Width, 1);
	m_outputSize.Height = max(m_outputSize.Height, 1);
}

// 이 메서드는 CoreWindow를 만들거나 다시 만들 때 호출됩니다.
void DX::DeviceResources::SetWindow(CoreWindow^ window)
{
	DisplayInformation^ currentDisplayInformation = DisplayInformation::GetForCurrentView();

	m_window = window;
	m_logicalSize = Windows::Foundation::Size(window->Bounds.Width, window->Bounds.Height);
	m_nativeOrientation = currentDisplayInformation->NativeOrientation;
	m_currentOrientation = currentDisplayInformation->CurrentOrientation;
	m_dpi = currentDisplayInformation->LogicalDpi;
	m_d2dContext->SetDpi(m_dpi, m_dpi);

	CreateWindowSizeDependentResources();
}

// 이 메서드는 SizeChanged 이벤트의 이벤트 처리기에서 호출됩니다.
void DX::DeviceResources::SetLogicalSize(Windows::Foundation::Size logicalSize)
{
	if (m_logicalSize != logicalSize)
	{
		m_logicalSize = logicalSize;
		CreateWindowSizeDependentResources();
	}
}

// 이 메서드는 DpiChanged 이벤트의 이벤트 처리기에서 호출됩니다.
void DX::DeviceResources::SetDpi(float dpi)
{
	if (dpi != m_dpi)
	{
		m_dpi = dpi;

		// 디스플레이 DPI가 변경된 경우 창의 논리적 크기(DIP 단위로 측정)도 변경되며 업데이트해야 합니다.
		m_logicalSize = Windows::Foundation::Size(m_window->Bounds.Width, m_window->Bounds.Height);

		m_d2dContext->SetDpi(m_dpi, m_dpi);
		CreateWindowSizeDependentResources();
	}
}

// 이 메서드는 OrientationChanged 이벤트의 이벤트 처리기에서 호출됩니다.
void DX::DeviceResources::SetCurrentOrientation(DisplayOrientations currentOrientation)
{
	if (m_currentOrientation != currentOrientation)
	{
		m_currentOrientation = currentOrientation;
		CreateWindowSizeDependentResources();
	}
}

// 이 메서드는 DisplayContentsInvalidated 이벤트의 이벤트 처리기에서 호출됩니다.
void DX::DeviceResources::ValidateDevice()
{
	// 기본 어댑터가 디바이스가 만들어진 이후에 변경되거나 디바이스가 제거된 경우
	// D3D 디바이스는 더 이상 유효하지 않습니다.

	// 먼저, 디바이스를 만들었을 때의 기본 어댑터에 대한 정보를 가져옵니다.

	ComPtr<IDXGIDevice3> dxgiDevice;
	DX::ThrowIfFailed(m_d3dDevice.As(&dxgiDevice));

	ComPtr<IDXGIAdapter> deviceAdapter;
	DX::ThrowIfFailed(dxgiDevice->GetAdapter(&deviceAdapter));

	ComPtr<IDXGIFactory4> deviceFactory;
	DX::ThrowIfFailed(deviceAdapter->GetParent(IID_PPV_ARGS(&deviceFactory)));

	ComPtr<IDXGIAdapter1> previousDefaultAdapter;
	DX::ThrowIfFailed(deviceFactory->EnumAdapters1(0, &previousDefaultAdapter));

	DXGI_ADAPTER_DESC1 previousDesc;
	DX::ThrowIfFailed(previousDefaultAdapter->GetDesc1(&previousDesc));

	// 다음으로, 현재 기본 어댑터에 대한 정보를 가져옵니다.

	ComPtr<IDXGIFactory4> currentFactory;
	DX::ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&currentFactory)));

	ComPtr<IDXGIAdapter1> currentDefaultAdapter;
	DX::ThrowIfFailed(currentFactory->EnumAdapters1(0, &currentDefaultAdapter));

	DXGI_ADAPTER_DESC1 currentDesc;
	DX::ThrowIfFailed(currentDefaultAdapter->GetDesc1(&currentDesc));

	// 어댑터 LUID가 일치하지 않거나 디바이스가 제거되었다고 보고하는 경우
	// 새 D3D 디바이스를 만들어야 합니다.

	if (previousDesc.AdapterLuid.LowPart != currentDesc.AdapterLuid.LowPart ||
		previousDesc.AdapterLuid.HighPart != currentDesc.AdapterLuid.HighPart ||
		FAILED(m_d3dDevice->GetDeviceRemovedReason()))
	{
		// 이전 디바이스와 관련된 리소스에 대한 참조를 해제합니다.
		dxgiDevice = nullptr;
		deviceAdapter = nullptr;
		deviceFactory = nullptr;
		previousDefaultAdapter = nullptr;

		// 새 디바이스 및 스왑 체인을 만듭니다.
		HandleDeviceLost();
	}
}

// 모든 디바이스 리소스를 다시 만들고 현재 상태로 다시 설정합니다.
void DX::DeviceResources::HandleDeviceLost()
{
	m_swapChain = nullptr;

	if (m_deviceNotify != nullptr)
	{
		m_deviceNotify->OnDeviceLost();
	}

	CreateDeviceResources();
	m_d2dContext->SetDpi(m_dpi, m_dpi);
	CreateWindowSizeDependentResources();

	if (m_deviceNotify != nullptr)
	{
		m_deviceNotify->OnDeviceRestored();
	}
}

// 장치 손실 및 생성에 대한 알림을 제공할 DeviceNotify를 등록합니다.
void DX::DeviceResources::RegisterDeviceNotify(DX::IDeviceNotify* deviceNotify)
{
	m_deviceNotify = deviceNotify;
}

// 앱이 일시 중단되면 이 메서드를 호출합니다. 앱이 유휴 상태에 들어가고 있고 다른 앱에서 사용하기 위해 
// 임시 버퍼가 회수될 수 있음을 드라이버에 알립니다.
void DX::DeviceResources::Trim()
{
	ComPtr<IDXGIDevice3> dxgiDevice;
	m_d3dDevice.As(&dxgiDevice);

	dxgiDevice->Trim();
}

// 스왑 체인의 콘텐츠를 화면에 표시합니다.
void DX::DeviceResources::Present() 
{
	// 첫 번째 인수는 DXGI에 VSync까지 차단하도록 지시하여 애플리케이션이
	// 다음 VSync까지 대기하도록 합니다. 이를 통해 화면에 표시되지 않는 프레임을
	// 렌더링하는 주기를 낭비하지 않을 수 있습니다.
	DXGI_PRESENT_PARAMETERS parameters = { 0 };
	HRESULT hr = m_swapChain->Present1(1, 0, &parameters);

	// 렌더링 대상의 콘텐츠를 삭제합니다.
	// 이 작업은 기존 콘텐츠를 완전히 덮어쓸 경우에만
	// 올바릅니다. 변경 또는 스크롤 영역이 사용되는 경우에는 이 호출을 제거해야 합니다.
	m_d3dContext->DiscardView1(m_d3dRenderTargetView.Get(), nullptr, 0);

	// 깊이 스텐실의 콘텐츠를 삭제합니다.
	m_d3dContext->DiscardView1(m_d3dDepthStencilView.Get(), nullptr, 0);

	// 연결이 끊기거나 드라이버 업그레이드로 인해 디바이스가 제거되면 
	// 모든 디바이스 리소스를 다시 만들어야 합니다.
	if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
	{
		HandleDeviceLost();
	}
	else
	{
		DX::ThrowIfFailed(hr);
	}
}

// 이 메서드는 디스플레이 디바이스의 기본 방향과 현재 디스플레이 방향 간의 회전을
// 확인합니다.
DXGI_MODE_ROTATION DX::DeviceResources::ComputeDisplayRotation()
{
	DXGI_MODE_ROTATION rotation = DXGI_MODE_ROTATION_UNSPECIFIED;

	// 참고: NativeOrientation은 DisplayOrientations 열거형이 다른 값을 포함하더라도
	// Landscape 또는 Portrait만 될 수 있습니다.
	switch (m_nativeOrientation)
	{
	case DisplayOrientations::Landscape:
		switch (m_currentOrientation)
		{
		case DisplayOrientations::Landscape:
			rotation = DXGI_MODE_ROTATION_IDENTITY;
			break;

		case DisplayOrientations::Portrait:
			rotation = DXGI_MODE_ROTATION_ROTATE270;
			break;

		case DisplayOrientations::LandscapeFlipped:
			rotation = DXGI_MODE_ROTATION_ROTATE180;
			break;

		case DisplayOrientations::PortraitFlipped:
			rotation = DXGI_MODE_ROTATION_ROTATE90;
			break;
		}
		break;

	case DisplayOrientations::Portrait:
		switch (m_currentOrientation)
		{
		case DisplayOrientations::Landscape:
			rotation = DXGI_MODE_ROTATION_ROTATE90;
			break;

		case DisplayOrientations::Portrait:
			rotation = DXGI_MODE_ROTATION_IDENTITY;
			break;

		case DisplayOrientations::LandscapeFlipped:
			rotation = DXGI_MODE_ROTATION_ROTATE270;
			break;

		case DisplayOrientations::PortraitFlipped:
			rotation = DXGI_MODE_ROTATION_ROTATE180;
			break;
		}
		break;
	}
	return rotation;
}