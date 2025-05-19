#include "CogEditorImguiContext.h"

#include "CogImguiHelper.h"
#include "CogImguiInputCatcherWidget.h"
#include "CogImguiWidget.h"
#include "imgui_internal.h"
#include "Interfaces/IMainFrameModule.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

#include "implot.h"
#include "Framework/Application/SlateApplication.h"

void FCogEditorImguiContext::Initialize()
{
    IMGUI_CHECKVERSION();

	IMainFrameModule& MainFrameModule = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
	TSharedPtr<SWindow> MainWindow = MainFrameModule.GetParentWindow();

    // ImGui Context must be created before creating widgets as widgets can receive events that uses the ImGui context right away.
    Context = ImGui::CreateContext();
    PlotContext = ImPlot::CreateContext();
    ImGui::SetCurrentContext(Context);
    ImPlot::SetImGuiContext(Context);
    ImPlot::SetCurrentContext(PlotContext);

	SAssignNew(MainWidget, SCogImguiWidget).Context(this);
	SAssignNew(InputCatcherWidget, SCogImguiInputCatcherWidget).Context(this);
	MainWindow->AddOverlaySlot() [
		MainWidget.ToSharedRef()
	];
	MainWindow->AddOverlaySlot() [
		InputCatcherWidget.ToSharedRef()
	];

    ImGuiIO& IO = ImGui::GetIO();
    IO.UserData = this;


    IO.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    IO.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    IO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    IO.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    IO.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    IO.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
    IO.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;
    IO.BackendFlags |= ImGuiBackendFlags_HasMouseHoveredViewport;
    IO.BackendFlags |= ImGuiBackendFlags_RendererHasViewports;
    IO.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;

    //--------------------------------------------------------------------
    // 
    //--------------------------------------------------------------------
    ImGuiViewport* MainViewport = ImGui::GetMainViewport();
    FCogImGuiViewportData* ViewportData = new FCogImGuiViewportData();
    MainViewport->PlatformUserData = ViewportData;
    ViewportData->Window = FSlateApplication::IsInitialized() ? FSlateApplication::Get().GetActiveTopLevelWindow() : nullptr;
    ViewportData->Context = this;
    ViewportData->Widget = MainWidget;

    const auto InitFilenameTemp = StringCast<ANSICHAR>(*FCogImguiHelper::GetIniFilePath("imgui"));
    ImStrncpy(IniFilename, InitFilenameTemp.Get(), IM_ARRAYSIZE(IniFilename));
    IO.IniFilename = IniFilename;

    ImGuiPlatformIO& PlatformIO = ImGui::GetPlatformIO();
    PlatformIO.Platform_CreateWindow = ImGui_CreateWindow;
    PlatformIO.Platform_DestroyWindow = ImGui_DestroyWindow;
    PlatformIO.Platform_ShowWindow = ImGui_ShowWindow;
    PlatformIO.Platform_SetWindowPos = ImGui_SetWindowPos;
    PlatformIO.Platform_GetWindowPos = ImGui_GetWindowPos;
    PlatformIO.Platform_SetWindowSize = ImGui_SetWindowSize;
    PlatformIO.Platform_GetWindowSize = ImGui_GetWindowSize;
    PlatformIO.Platform_SetWindowFocus = ImGui_SetWindowFocus;
    PlatformIO.Platform_GetWindowFocus = ImGui_GetWindowFocus;
    PlatformIO.Platform_GetWindowMinimized = ImGui_GetWindowMinimized;
    PlatformIO.Platform_SetWindowTitle = ImGui_SetWindowTitle;
    PlatformIO.Platform_SetWindowAlpha = ImGui_SetWindowAlpha;
    PlatformIO.Platform_RenderWindow = ImGui_RenderWindow;
    
    PlatformIO.Platform_ClipboardUserData = &ClipboardBuffer;
    PlatformIO.Platform_GetClipboardTextFn = ImGui_GetClipboardTextFn;
    PlatformIO.Platform_SetClipboardTextFn = ImGui_SetClipboardTextFn;
    PlatformIO.Platform_OpenInShellFn = ImGui_OpenInShell;

    if (FSlateApplication::IsInitialized())
    {
        if (const TSharedPtr<GenericApplication> PlatformApplication = FSlateApplication::Get().GetPlatformApplication())
        {
            FDisplayMetrics DisplayMetrics;
            PlatformApplication->GetInitialDisplayMetrics(DisplayMetrics);
            PlatformApplication->OnDisplayMetricsChanged().AddRaw(this, &FCogEditorImguiContext::OnDisplayMetricsChanged);
            OnDisplayMetricsChanged(DisplayMetrics);
        }
    }
    else
    {
        FMonitorInfo monitorInfo;
        monitorInfo.bIsPrimary = true;
        monitorInfo.DisplayRect = FPlatformRect(0, 0, 1080, 720);
        FDisplayMetrics DisplayMetrics;
        DisplayMetrics.MonitorInfo.Add(monitorInfo);
        OnDisplayMetricsChanged(DisplayMetrics);
    }

#if NETIMGUI_ENABLED
    if (bIsNetImGuiInitialized == false)
    {
        NetImgui::Startup();
        bIsNetImGuiInitialized = true;
    }
#endif	
}
