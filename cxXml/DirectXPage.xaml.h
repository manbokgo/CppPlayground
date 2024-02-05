//
// DirectXPage.xaml.h
// DirectXPage 클래스의 선언입니다.
//

#pragma once

#include "DirectXPage.g.h"

#include "Common\DeviceResources.h"
#include "cxXmlMain.h"

namespace cxXml
{
	/// <summary>
	/// DirectX SwapChainPanel을 호스트하는 페이지입니다.
	/// </summary>
	public ref class DirectXPage sealed
	{
	public:
		DirectXPage();
		virtual ~DirectXPage();

		void SaveInternalState(Windows::Foundation::Collections::IPropertySet^ state);
		void LoadInternalState(Windows::Foundation::Collections::IPropertySet^ state);

	private:
		// XAML 하위 수준 렌더링 이벤트 처리기입니다.
		void OnRendering(Platform::Object^ sender, Platform::Object^ args);

		// 창 이벤트 처리기입니다.
		void OnVisibilityChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::VisibilityChangedEventArgs^ args);

		// DisplayInformation 이벤트 처리기입니다.
		void OnDpiChanged(Windows::Graphics::Display::DisplayInformation^ sender, Platform::Object^ args);
		void OnOrientationChanged(Windows::Graphics::Display::DisplayInformation^ sender, Platform::Object^ args);
		void OnDisplayContentsInvalidated(Windows::Graphics::Display::DisplayInformation^ sender, Platform::Object^ args);

		// 기타 이벤트 처리기입니다.
		void AppBarButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnCompositionScaleChanged(Windows::UI::Xaml::Controls::SwapChainPanel^ sender, Object^ args);
		void OnSwapChainPanelSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ e);

		// 백그라운드 작업자 스레드에서 독립 입력을 추적합니다.
		Windows::Foundation::IAsyncAction^ m_inputLoopWorker;
		Windows::UI::Core::CoreIndependentInputSource^ m_coreInput;

		// 독립 입력 처리 함수입니다.
		void OnPointerPressed(Platform::Object^ sender, Windows::UI::Core::PointerEventArgs^ e);
		void OnPointerMoved(Platform::Object^ sender, Windows::UI::Core::PointerEventArgs^ e);
		void OnPointerReleased(Platform::Object^ sender, Windows::UI::Core::PointerEventArgs^ e);

		// XAML 페이지 백그라운드에서 DirectX 콘텐츠를 렌더링하는 데 사용되는 리소스입니다.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;
		std::unique_ptr<cxXmlMain> m_main; 
		bool m_windowVisible;
	};
}

