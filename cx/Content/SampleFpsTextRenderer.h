#pragma once

#include <string>
#include "..\Common\DeviceResources.h"
#include "..\Common\StepTimer.h"

namespace cx
{
	// Direct2D 및 DirectWrite를 사용하여 화면 오른쪽 맨 아래 모퉁이에서 현재 FPS 값을 렌더링합니다.
	class SampleFpsTextRenderer
	{
	public:
		SampleFpsTextRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void CreateDeviceDependentResources();
		void ReleaseDeviceDependentResources();
		void Update(DX::StepTimer const& timer);
		void Render();

	private:
		// 디바이스 리소스에 대한 캐시된 포인터입니다.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// 텍스트 렌더링 관련 리소스입니다.
		std::wstring                                    m_text;
		DWRITE_TEXT_METRICS	                            m_textMetrics;
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>    m_whiteBrush;
		Microsoft::WRL::ComPtr<ID2D1DrawingStateBlock1> m_stateBlock;
		Microsoft::WRL::ComPtr<IDWriteTextLayout3>      m_textLayout;
		Microsoft::WRL::ComPtr<IDWriteTextFormat2>      m_textFormat;
	};
}