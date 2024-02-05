#pragma once

#include "..\Common\DeviceResources.h"
#include "ShaderStructures.h"
#include "..\Common\StepTimer.h"

namespace cx
{
	// 이 샘플 렌더러는 기본 렌더링 파이프라인을 인스턴스화합니다.
	class Sample3DSceneRenderer
	{
	public:
		Sample3DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void CreateDeviceDependentResources();
		void CreateWindowSizeDependentResources();
		void ReleaseDeviceDependentResources();
		void Update(DX::StepTimer const& timer);
		void Render();
		void StartTracking();
		void TrackingUpdate(float positionX);
		void StopTracking();
		bool IsTracking() { return m_tracking; }


	private:
		void Rotate(float radians);

	private:
		// 디바이스 리소스에 대한 캐시된 포인터입니다.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// 큐브 기하 도형의 Direct3D 리소스입니다.
		Microsoft::WRL::ComPtr<ID3D11InputLayout>	m_inputLayout;
		Microsoft::WRL::ComPtr<ID3D11Buffer>		m_vertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer>		m_indexBuffer;
		Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_vertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_pixelShader;
		Microsoft::WRL::ComPtr<ID3D11Buffer>		m_constantBuffer;

		// 큐브 기하 도형의 시스템 리소스입니다.
		ModelViewProjectionConstantBuffer	m_constantBufferData;
		uint32	m_indexCount;

		// 렌더링 루프에 사용되는 변수입니다.
		bool	m_loadingComplete;
		float	m_degreesPerSecond;
		bool	m_tracking;
	};
}

