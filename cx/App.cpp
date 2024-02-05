#include "pch.h"
#include "App.h"

#include <ppltasks.h>

using namespace cx;

using namespace concurrency;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Input;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;

// main 함수는 IFrameworkView 클래스 초기화에만 사용됩니다.
[Platform::MTAThread]
int main(Platform::Array<Platform::String^>^)
{
	auto direct3DApplicationSource = ref new Direct3DApplicationSource();
	CoreApplication::Run(direct3DApplicationSource);
	return 0;
}

IFrameworkView^ Direct3DApplicationSource::CreateView()
{
	return ref new App();
}

App::App() :
	m_windowClosed(false),
	m_windowVisible(true)
{
}

// IFrameworkView를 만들 때 호출되는 첫 번째 메서드입니다.
void App::Initialize(CoreApplicationView^ applicationView)
{
	// 응용 프로그램 수명 주기의 이벤트 처리기를 등록합니다. 이 예에는 Activated가 포함되므로
	// CoreWindow를 활성 상태로 만들고 창에서 렌더링을 시작할 수 있습니다.
	applicationView->Activated +=
		ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(this, &App::OnActivated);

	CoreApplication::Suspending +=
		ref new EventHandler<SuspendingEventArgs^>(this, &App::OnSuspending);

	CoreApplication::Resuming +=
		ref new EventHandler<Platform::Object^>(this, &App::OnResuming);

	// 여기서 디바이스에 액세스할 수 있습니다. 
	// 디바이스 종속적 리소스를 만들 수 있습니다.
	m_deviceResources = std::make_shared<DX::DeviceResources>();
}

// CoreWindow 개체가 생성(또는 다시 생성)될 때 호출됩니다.
void App::SetWindow(CoreWindow^ window)
{
	window->SizeChanged += 
		ref new TypedEventHandler<CoreWindow^, WindowSizeChangedEventArgs^>(this, &App::OnWindowSizeChanged);

	window->VisibilityChanged +=
		ref new TypedEventHandler<CoreWindow^, VisibilityChangedEventArgs^>(this, &App::OnVisibilityChanged);

	window->Closed += 
		ref new TypedEventHandler<CoreWindow^, CoreWindowEventArgs^>(this, &App::OnWindowClosed);

	DisplayInformation^ currentDisplayInformation = DisplayInformation::GetForCurrentView();

	currentDisplayInformation->DpiChanged +=
		ref new TypedEventHandler<DisplayInformation^, Object^>(this, &App::OnDpiChanged);

	currentDisplayInformation->OrientationChanged +=
		ref new TypedEventHandler<DisplayInformation^, Object^>(this, &App::OnOrientationChanged);

	DisplayInformation::DisplayContentsInvalidated +=
		ref new TypedEventHandler<DisplayInformation^, Object^>(this, &App::OnDisplayContentsInvalidated);

	m_deviceResources->SetWindow(window);
}

// 장면 리소스를 초기화하거나 이전에 저장한 응용 프로그램 상태를 로드합니다.
void App::Load(Platform::String^ entryPoint)
{
	if (m_main == nullptr)
	{
		m_main = std::unique_ptr<cxMain>(new cxMain(m_deviceResources));
	}
}

// 이 메서드는 창이 활성화된 후 호출됩니다.
void App::Run()
{
	while (!m_windowClosed)
	{
		if (m_windowVisible)
		{
			CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);

			m_main->Update();

			if (m_main->Render())
			{
				m_deviceResources->Present();
			}
		}
		else
		{
			CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessOneAndAllPending);
		}
	}
}

// IFrameworkView에 필요합니다.
// 종료 이벤트는 Uninitialize를 호출하지 않습니다. Uninitialize는
// 응용 프로그램이 전경에 있는 동안 IFrameworkView 클래스가 삭제되는 경우에 호출됩니다.
void App::Uninitialize()
{
}

// 애플리케이션 수명 주기 이벤트 처리기입니다.

void App::OnActivated(CoreApplicationView^ applicationView, IActivatedEventArgs^ args)
{
	// CoreWindow가 활성화되어야 Run()이 시작됩니다.
	CoreWindow::GetForCurrentThread()->Activate();
}

void App::OnSuspending(Platform::Object^ sender, SuspendingEventArgs^ args)
{
	// 지연을 요청한 후 응용 프로그램 상태를 비동기적으로 저장합니다. 지연이 계속되는 것은
	// 애플리케이션이 일시 중단 중인 작업을 수행하는 중이라는 의미입니다.
	// 지연은 무기한 지속되지 않습니다. 약 5초 후
	// 앱이 강제로 종료됩니다.
	SuspendingDeferral^ deferral = args->SuspendingOperation->GetDeferral();

	create_task([this, deferral]()
	{
        m_deviceResources->Trim();

		// 여기에 코드를 삽입합니다.

		deferral->Complete();
	});
}

void App::OnResuming(Platform::Object^ sender, Platform::Object^ args)
{
	// 일시 중단 시 언로드된 모든 데이터 또는 상태를 복원합니다. 기본적으로 데이터
	// 및 상태는 일시 중단 이후 다시 시작할 때 유지됩니다. 이 이벤트는
	// 응용 프로그램을 이전에 종료한 경우 발생하지 않습니다.

	// 여기에 코드를 삽입합니다.
}

// 창 이벤트 처리기입니다.

void App::OnWindowSizeChanged(CoreWindow^ sender, WindowSizeChangedEventArgs^ args)
{
	m_deviceResources->SetLogicalSize(Size(sender->Bounds.Width, sender->Bounds.Height));
	m_main->CreateWindowSizeDependentResources();
}

void App::OnVisibilityChanged(CoreWindow^ sender, VisibilityChangedEventArgs^ args)
{
	m_windowVisible = args->Visible;
}

void App::OnWindowClosed(CoreWindow^ sender, CoreWindowEventArgs^ args)
{
	m_windowClosed = true;
}

// DisplayInformation 이벤트 처리기입니다.

void App::OnDpiChanged(DisplayInformation^ sender, Object^ args)
{
	// 참고: 여기에서 검색된 LogicalDpi의 값은 고해상도 장치용으로 크기가 조정되는 경우
	// 앱의 유효 DPI와 일치하지 않을 수 있습니다. DPI가 DeviceResources에서 설정되면
	// 항상 GetDpi 메서드를 사용하여 DPI를 검색해야 합니다.
	// 자세한 내용은 DeviceResources.cpp를 참조하세요.
	m_deviceResources->SetDpi(sender->LogicalDpi);
	m_main->CreateWindowSizeDependentResources();
}

void App::OnOrientationChanged(DisplayInformation^ sender, Object^ args)
{
	m_deviceResources->SetCurrentOrientation(sender->CurrentOrientation);
	m_main->CreateWindowSizeDependentResources();
}

void App::OnDisplayContentsInvalidated(DisplayInformation^ sender, Object^ args)
{
	m_deviceResources->ValidateDevice();
}