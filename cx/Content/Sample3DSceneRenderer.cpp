#include "pch.h"
#include "Sample3DSceneRenderer.h"

#include "..\Common\DirectXHelper.h"

using namespace cx;

using namespace DirectX;
using namespace Windows::Foundation;

// 파일에서 꼭짓점 및 픽셀 셰이더를 로드하고 큐브 기하 도형을 인스턴스화합니다.
Sample3DSceneRenderer::Sample3DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources) :
	m_loadingComplete(false),
	m_degreesPerSecond(45),
	m_indexCount(0),
	m_tracking(false),
	m_deviceResources(deviceResources)
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}

// 창 크기가 변경되면 뷰 매개 변수를 초기화합니다.
void Sample3DSceneRenderer::CreateWindowSizeDependentResources()
{
	Size outputSize = m_deviceResources->GetOutputSize();
	float aspectRatio = outputSize.Width / outputSize.Height;
	float fovAngleY = 70.0f * XM_PI / 180.0f;

	// 앱이 세로 뷰 또는 기본 뷰인 경우 수행할 수 있는 간단한
	// 변경의 예입니다.
	if (aspectRatio < 1.0f)
	{
		fovAngleY *= 2.0f;
	}

	// 여기에서 OrientationTransform3D 매트릭스는 표시 방향에 맞게
	// 장면 방향을 올바르게 지정하기 위해 사후 곱셈됩니다.
	// 이 사후 곱셈 단계는
	// 스왑 체인 렌더링 대상에 대한 모든 그리기 호출 시 필요합니다. 다른 대상에 대한 그리기 호출의 경우
	// 이 변환을 적용해서는 안 됩니다.

	// 이 샘플에서는 행 중심 매트릭스를 사용하는 오른손 좌표계를 이용합니다.
	XMMATRIX perspectiveMatrix = XMMatrixPerspectiveFovRH(
		fovAngleY,
		aspectRatio,
		0.01f,
		100.0f
		);

	XMFLOAT4X4 orientation = m_deviceResources->GetOrientationTransform3D();

	XMMATRIX orientationMatrix = XMLoadFloat4x4(&orientation);

	XMStoreFloat4x4(
		&m_constantBufferData.projection,
		XMMatrixTranspose(perspectiveMatrix * orientationMatrix)
		);

	// 시선은 y축을 따라 업 벡터가 있는 상태로 점 (0,-0.1,0)를 보며 (0,0.7,1.5)에 있습니다.
	static const XMVECTORF32 eye = { 0.0f, 0.7f, 1.5f, 0.0f };
	static const XMVECTORF32 at = { 0.0f, -0.1f, 0.0f, 0.0f };
	static const XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };

	XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));
}

// 프레임당 한 번 호출됩니다. 큐브를 회전하고 모델 및 뷰 매트릭스를 계산합니다.
void Sample3DSceneRenderer::Update(DX::StepTimer const& timer)
{
	if (!m_tracking)
	{
		// 도를 라디언으로 변환한 다음 초를 회전 각도로 변환합니다.
		float radiansPerSecond = XMConvertToRadians(m_degreesPerSecond);
		double totalRotation = timer.GetTotalSeconds() * radiansPerSecond;
		float radians = static_cast<float>(fmod(totalRotation, XM_2PI));

		Rotate(radians);
	}
}

// 3D 큐브 모델에 라디안 설정 값을 회전합니다.
void Sample3DSceneRenderer::Rotate(float radians)
{
	// 업데이트된 모델 매트릭스를 셰이더에 전달하도록 준비합니다.
	XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixTranspose(XMMatrixRotationY(radians)));
}

void Sample3DSceneRenderer::StartTracking()
{
	m_tracking = true;
}

// 추적할 때 3D 큐브는 화면 출력 너비에 상대적인 포인터 위치를 추적하여 Y축을 중심으로 회전할 수 있습니다.
void Sample3DSceneRenderer::TrackingUpdate(float positionX)
{
	if (m_tracking)
	{
		float radians = XM_2PI * 2.0f * positionX / m_deviceResources->GetOutputSize().Width;
		Rotate(radians);
	}
}

void Sample3DSceneRenderer::StopTracking()
{
	m_tracking = false;
}

// 꼭짓점 및 픽셀 셰이더를 사용하여 한 프레임을 렌더링합니다.
void Sample3DSceneRenderer::Render()
{
	// 로드는 비동기로 수행됩니다. 기하 도형의 로드가 완료되어야 해당 기하 도형을 그립니다.
	if (!m_loadingComplete)
	{
		return;
	}

	auto context = m_deviceResources->GetD3DDeviceContext();

	// 그래픽 디바이스로 보낼 수 있도록 상수 버퍼를 준비합니다.
	context->UpdateSubresource1(
		m_constantBuffer.Get(),
		0,
		NULL,
		&m_constantBufferData,
		0,
		0,
		0
		);

	// 각 꼭짓점은 VertexPositionColor 구조체의 한 인스턴스입니다.
	UINT stride = sizeof(VertexPositionColor);
	UINT offset = 0;
	context->IASetVertexBuffers(
		0,
		1,
		m_vertexBuffer.GetAddressOf(),
		&stride,
		&offset
		);

	context->IASetIndexBuffer(
		m_indexBuffer.Get(),
		DXGI_FORMAT_R16_UINT, // 각 인덱스는 하나의 부호 없는 16비트 정수(Short)입니다.
		0
		);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	context->IASetInputLayout(m_inputLayout.Get());

	// 꼭짓점 셰이더를 연결합니다.
	context->VSSetShader(
		m_vertexShader.Get(),
		nullptr,
		0
		);

	// 상수 버퍼를 그래픽 디바이스에 보냅니다.
	context->VSSetConstantBuffers1(
		0,
		1,
		m_constantBuffer.GetAddressOf(),
		nullptr,
		nullptr
		);

	// 픽셀 셰이더를 연결합니다.
	context->PSSetShader(
		m_pixelShader.Get(),
		nullptr,
		0
		);

	// 개체를 그립니다.
	context->DrawIndexed(
		m_indexCount,
		0,
		0
		);
}

void Sample3DSceneRenderer::CreateDeviceDependentResources()
{
	// 셰이더를 비동기적으로 로드합니다.
	auto loadVSTask = DX::ReadDataAsync(L"SampleVertexShader.cso");
	auto loadPSTask = DX::ReadDataAsync(L"SamplePixelShader.cso");

	// 꼭짓점 셰이더 파일이 로드되면 셰이더 및 입력 레이아웃을 만듭니다.
	auto createVSTask = loadVSTask.then([this](const std::vector<byte>& fileData) {
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateVertexShader(
				&fileData[0],
				fileData.size(),
				nullptr,
				&m_vertexShader
				)
			);

		static const D3D11_INPUT_ELEMENT_DESC vertexDesc [] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateInputLayout(
				vertexDesc,
				ARRAYSIZE(vertexDesc),
				&fileData[0],
				fileData.size(),
				&m_inputLayout
				)
			);
	});

	// 픽셀 셰이더 파일이 로드되면 셰이더 및 상수 버퍼를 만듭니다.
	auto createPSTask = loadPSTask.then([this](const std::vector<byte>& fileData) {
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreatePixelShader(
				&fileData[0],
				fileData.size(),
				nullptr,
				&m_pixelShader
				)
			);

		CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelViewProjectionConstantBuffer) , D3D11_BIND_CONSTANT_BUFFER);
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateBuffer(
				&constantBufferDesc,
				nullptr,
				&m_constantBuffer
				)
			);
	});

	// 두 셰이더가 모두 로드되면 메시를 만듭니다.
	auto createCubeTask = (createPSTask && createVSTask).then([this] () {

		// 메시 꼭짓점을 로드합니다. 각 꼭짓점은 위치 및 색을 가지고 있습니다.
		static const VertexPositionColor cubeVertices[] = 
		{
			{XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f)},
			{XMFLOAT3(-0.5f, -0.5f,  0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f)},
			{XMFLOAT3(-0.5f,  0.5f, -0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f)},
			{XMFLOAT3(-0.5f,  0.5f,  0.5f), XMFLOAT3(0.0f, 1.0f, 1.0f)},
			{XMFLOAT3( 0.5f, -0.5f, -0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f)},
			{XMFLOAT3( 0.5f, -0.5f,  0.5f), XMFLOAT3(1.0f, 0.0f, 1.0f)},
			{XMFLOAT3( 0.5f,  0.5f, -0.5f), XMFLOAT3(1.0f, 1.0f, 0.0f)},
			{XMFLOAT3( 0.5f,  0.5f,  0.5f), XMFLOAT3(1.0f, 1.0f, 1.0f)},
		};

		D3D11_SUBRESOURCE_DATA vertexBufferData = {0};
		vertexBufferData.pSysMem = cubeVertices;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(cubeVertices), D3D11_BIND_VERTEX_BUFFER);
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateBuffer(
				&vertexBufferDesc,
				&vertexBufferData,
				&m_vertexBuffer
				)
			);

		// 메시 인덱스를 로드합니다. 각 인덱스의 3개 숫자는
		// 화면에 렌더링할 삼각형을 나타냅니다.
		// 예를 들어 0,2,1은 인덱스로 꼭짓점을 의미합니다.
		// 0, 2 및 1인 꼭짓점이 이 메시의 첫 번째 삼각형을
		// 구성함을 의미합니다.
		static const unsigned short cubeIndices [] =
		{
			0,2,1, // -x
			1,2,3,

			4,5,6, // +x
			5,7,6,

			0,1,5, // -y
			0,5,4,

			2,6,7, // +y
			2,7,3,

			0,4,6, // -z
			0,6,2,

			1,3,7, // +z
			1,7,5,
		};

		m_indexCount = ARRAYSIZE(cubeIndices);

		D3D11_SUBRESOURCE_DATA indexBufferData = {0};
		indexBufferData.pSysMem = cubeIndices;
		indexBufferData.SysMemPitch = 0;
		indexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC indexBufferDesc(sizeof(cubeIndices), D3D11_BIND_INDEX_BUFFER);
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateBuffer(
				&indexBufferDesc,
				&indexBufferData,
				&m_indexBuffer
				)
			);
	});

	// 큐브가 로드되면 개체가 렌더링할 수 있도록 준비됩니다.
	createCubeTask.then([this] () {
		m_loadingComplete = true;
	});
}

void Sample3DSceneRenderer::ReleaseDeviceDependentResources()
{
	m_loadingComplete = false;
	m_vertexShader.Reset();
	m_inputLayout.Reset();
	m_pixelShader.Reset();
	m_constantBuffer.Reset();
	m_vertexBuffer.Reset();
	m_indexBuffer.Reset();
}