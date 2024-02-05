//
// DirectXPage.xaml.cpp
// DirectXPage 클래스의 구현입니다.
//

#include "pch.h"
#include "DirectXPage.xaml.h"

using namespace cxXml;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Display;
using namespace Windows::System::Threading;
using namespace Windows::UI::Core;
using namespace Windows::UI::Input;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace concurrency;

DirectXPage::DirectXPage():
	m_windowVisible(true),
	m_coreInput(nullptr)
{
	InitializeComponent();

	// 페이지 수명 주기의 이벤트 처리기를 등록합니다.
	CoreWindow^ window = Window::Current->CoreWindow;

	window->VisibilityChanged +=
		ref new TypedEventHandler<CoreWindow^, VisibilityChangedEventArgs^>(this, &DirectXPage::OnVisibilityChanged);

	DisplayInformation^ currentDisplayInformation = DisplayInformation::GetForCurrentView();

	currentDisplayInformation->DpiChanged +=
		ref new TypedEventHandler<DisplayInformation^, Object^>(this, &DirectXPage::OnDpiChanged);

	currentDisplayInformation->OrientationChanged +=
		ref new TypedEventHandler<DisplayInformation^, Object^>(this, &DirectXPage::OnOrientationChanged);

	DisplayInformation::DisplayContentsInvalidated +=
		ref new TypedEventHandler<DisplayInformation^, Object^>(this, &DirectXPage::OnDisplayContentsInvalidated);

	swapChainPanel->CompositionScaleChanged += 
		ref new TypedEventHandler<SwapChainPanel^, Object^>(this, &DirectXPage::OnCompositionScaleChanged);

	swapChainPanel->SizeChanged +=
		ref new SizeChangedEventHandler(this, &DirectXPage::OnSwapChainPanelSizeChanged);

	// 여기서 디바이스에 액세스할 수 있습니다. 
	// 디바이스 종속적 리소스를 만들 수 있습니다.
	m_deviceResources = std::make_shared<DX::DeviceResources>();
	m_deviceResources->SetSwapChainPanel(swapChainPanel);

	// 독립 입력 포인터 이벤트를 얻으려면 SwapChainPanel을 등록합니다.
	auto workItemHandler = ref new WorkItemHandler([this] (IAsyncAction ^)
	{
		// CoreIndependentInputSource는 어떤 스레드가 만들어지던 특정 디바이스 유형에 대한 포인터 이벤트가 발생됩니다.
		m_coreInput = swapChainPanel->CreateCoreIndependentInputSource(
			Windows::UI::Core::CoreInputDeviceTypes::Mouse |
			Windows::UI::Core::CoreInputDeviceTypes::Touch |
			Windows::UI::Core::CoreInputDeviceTypes::Pen
			);

		// 백그라운드 스레드에서 발생할 포인터 이벤트를 등록합니다.
		m_coreInput->PointerPressed += ref new TypedEventHandler<Object^, PointerEventArgs^>(this, &DirectXPage::OnPointerPressed);
		m_coreInput->PointerMoved += ref new TypedEventHandler<Object^, PointerEventArgs^>(this, &DirectXPage::OnPointerMoved);
		m_coreInput->PointerReleased += ref new TypedEventHandler<Object^, PointerEventArgs^>(this, &DirectXPage::OnPointerReleased);

		// 전달된 대로 입력 메시지 처리를 시작합니다.
		m_coreInput->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessUntilQuit);
	});

	// 전용인 우선 순위가 높은 백그라운드 스레드에서 작업을 실행합니다.
	m_inputLoopWorker = ThreadPool::RunAsync(workItemHandler, WorkItemPriority::High, WorkItemOptions::TimeSliced);

	m_main = std::unique_ptr<cxXmlMain>(new cxXmlMain(m_deviceResources));
	m_main->StartRenderLoop();
}

DirectXPage::~DirectXPage()
{
	// 소멸에 대한 이벤트 렌더링 및 이벤트 처리를 중지합니다.
	m_main->StopRenderLoop();
	m_coreInput->Dispatcher->StopProcessEvents();
}

// 일시 중단 및 종료 이벤트에 대해 앱의 현재 상태를 저장합니다.
void DirectXPage::SaveInternalState(IPropertySet^ state)
{
	critical_section::scoped_lock lock(m_main->GetCriticalSection());
	m_deviceResources->Trim();

	// 앱이 중지되면 렌더링을 중지합니다.
	m_main->StopRenderLoop();

	// 여기에 응용 프로그램 상태를 저장할 코드를 입력합니다.
}

// 다시 시작 이벤트에 대해 앱의 현재 상태를 로드합니다.
void DirectXPage::LoadInternalState(IPropertySet^ state)
{
	// 여기에 앱 상태를 로드할 코드를 입력합니다.

	// 앱이 다시 시작되는 경우 렌더링을 시작합니다.
	m_main->StartRenderLoop();
}

// 창 이벤트 처리기입니다.

void DirectXPage::OnVisibilityChanged(CoreWindow^ sender, VisibilityChangedEventArgs^ args)
{
	m_windowVisible = args->Visible;
	if (m_windowVisible)
	{
		m_main->StartRenderLoop();
	}
	else
	{
		m_main->StopRenderLoop();
	}
}

// DisplayInformation 이벤트 처리기입니다.

void DirectXPage::OnDpiChanged(DisplayInformation^ sender, Object^ args)
{
	critical_section::scoped_lock lock(m_main->GetCriticalSection());
	// 참고: 여기에서 검색된 LogicalDpi의 값은 고해상도 장치용으로 크기가 조정되는 경우
	// 앱의 유효 DPI와 일치하지 않을 수 있습니다. DPI가 DeviceResources에서 설정되면
	// 항상 GetDpi 메서드를 사용하여 DPI를 검색해야 합니다.
	// 자세한 내용은 DeviceResources.cpp를 참조하세요.
	m_deviceResources->SetDpi(sender->LogicalDpi);
	m_main->CreateWindowSizeDependentResources();
}

void DirectXPage::OnOrientationChanged(DisplayInformation^ sender, Object^ args)
{
	critical_section::scoped_lock lock(m_main->GetCriticalSection());
	m_deviceResources->SetCurrentOrientation(sender->CurrentOrientation);
	m_main->CreateWindowSizeDependentResources();
}

void DirectXPage::OnDisplayContentsInvalidated(DisplayInformation^ sender, Object^ args)
{
	critical_section::scoped_lock lock(m_main->GetCriticalSection());
	m_deviceResources->ValidateDevice();
}

// 앱 바 단추를 클릭하면 호출됩니다.
void DirectXPage::AppBarButton_Click(Object^ sender, RoutedEventArgs^ e)
{
	// 앱에 적합한 앱 바가 있으면 사용하세요. 앱 바를 디자인합니다.
	// 그리고 다음과 같이 이벤트 처리기를 채웁니다.
}

void DirectXPage::OnPointerPressed(Object^ sender, PointerEventArgs^ e)
{
	// 포인터를 누르면 포인터 이동 추적을 시작합니다.
	m_main->StartTracking();
}

void DirectXPage::OnPointerMoved(Object^ sender, PointerEventArgs^ e)
{
	// 포인터 추적 코드를 업데이트합니다.
	if (m_main->IsTracking())
	{
		m_main->TrackingUpdate(e->CurrentPoint->Position.X);
	}
}

void DirectXPage::OnPointerReleased(Object^ sender, PointerEventArgs^ e)
{
	// 포인터가 해제되는 경우 추적 포인터 이동이 중지됩니다.
	m_main->StopTracking();
}

void DirectXPage::OnCompositionScaleChanged(SwapChainPanel^ sender, Object^ args)
{
	critical_section::scoped_lock lock(m_main->GetCriticalSection());
	m_deviceResources->SetCompositionScale(sender->CompositionScaleX, sender->CompositionScaleY);
	m_main->CreateWindowSizeDependentResources();
}

void DirectXPage::OnSwapChainPanelSizeChanged(Object^ sender, SizeChangedEventArgs^ e)
{
	critical_section::scoped_lock lock(m_main->GetCriticalSection());
	m_deviceResources->SetLogicalSize(e->NewSize);
	m_main->CreateWindowSizeDependentResources();
}
