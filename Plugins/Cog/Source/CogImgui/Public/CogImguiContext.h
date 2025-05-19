#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h" 
#include "imgui.h"
#include "Templates/SharedPointer.h"
#include "UObject/StrongObjectPtr.h"

class ICogImguiContext;
class FCogImguiContext;
class IInputProcessor;
class SCogImguiWidget;
class SCogImguiWidget;
class SCogImguiInputCatcherWidget;
class SWidget;
class SWindow;
class UGameViewportClient;
class ULocalPlayer;
struct FDisplayMetrics;
struct ImPlotContext;

struct COGIMGUI_API FCogImGuiViewportData
{
	TWeakPtr<SWindow> Window = nullptr;
	FCogImguiContext* Context = nullptr;
	TWeakPtr<SCogImguiWidget> Widget = nullptr;
};

class COGIMGUI_API ICogImguiContext 
{
public:
	virtual ~ICogImguiContext() {};

	virtual TObjectPtr<const UGameViewportClient> GetGameViewport() const PURE_VIRTUAL(GetGameViewport, return(nullptr); ); 
	virtual TSharedPtr<const SCogImguiWidget> GetMainWidget() const PURE_VIRTUAL(GetMainWidget, return(nullptr); );
	
	virtual ImGuiContext* GetImGuiContext() PURE_VIRTUAL(GetImGuiContext, return nullptr; ); 
	virtual ImPlotContext* GetImPlotContext() PURE_VIRTUAL(GetImPlotContext, return nullptr; );

	virtual bool GetEnableInput() const PURE_VIRTUAL(GetEnableInput, return false; );
	virtual void SetEnableInput(bool InValue) PURE_VIRTUAL(SetEnableInput);

	virtual bool GetShareKeyboard() const PURE_VIRTUAL(GetEnableKeyboard, return false; );
	virtual void SetShareKeyboard(bool InValue) PURE_VIRTUAL(SetShareKeyboard);

	virtual bool GetShareMouse() const PURE_VIRTUAL(GetShareMouse, return false; );
	virtual void SetShareMouse(bool InValue) PURE_VIRTUAL(SetShareMouse);

	virtual bool GetShareMouseWithGameplay() const PURE_VIRTUAL(GetShareMouseWithGameplay, return false; );
	virtual void SetShareMouseWithGameplay(bool InValue) PURE_VIRTUAL(SetShareMouseWithGameplay);
	
	virtual bool GetWantCaptureMouse() const PURE_VIRTUAL(GetWantCaptureMouse, return(false); );

	virtual float GetDPIScale() const PURE_VIRTUAL(GetDPIScale, return(0.0f); );
	virtual void SetDPIScale(float Value) PURE_VIRTUAL(SetDPIScale);
	
	virtual bool BeginFrame(float InDeltaTime) PURE_VIRTUAL(BeginFrame, return false; );
	virtual void EndFrame() PURE_VIRTUAL(EndFrame);
	
	virtual ImVec2 GetImguiMousePos() const PURE_VIRTUAL(GetImguiMousePos, return ImVec2{}; ); 
	
	virtual bool GetSkipRendering() const PURE_VIRTUAL(GetSkipRendering, return(false); ); 
	virtual void SetSkipRendering(bool skip) PURE_VIRTUAL(SkipRendering);
	
	virtual void SaveSettings() const PURE_VIRTUAL(SaveSettings);
	virtual void Shutdown() PURE_VIRTUAL(Shutdown);

	virtual void OnImGuiWidgetFocusLost() PURE_VIRTUAL(OnImGuiWidgetFocusLost);
};

struct COGIMGUI_API FCogImGuiContextScope
{
	UE_NODISCARD_CTOR explicit FCogImGuiContextScope(ICogImguiContext& CogImguiContext);
	UE_NODISCARD_CTOR explicit FCogImGuiContextScope(const FCogImguiContext& CogImguiContext);
	UE_NODISCARD_CTOR explicit FCogImGuiContextScope(ImGuiContext* GuiCtx, ImPlotContext* PlotCtx);
	~FCogImGuiContextScope();

protected:
	ImGuiContext* PrevContext = nullptr;
	ImPlotContext* PrevPlotContext = nullptr;
};

class COGIMGUI_API FCogImguiContext 
	:	public TSharedFromThis<FCogImguiContext>
	,	public ICogImguiContext
{
public:

#pragma region ICogImguiContext
	bool BeginFrame(float InDeltaTime) override;
	void EndFrame() override;
	
	ImGuiContext* GetImGuiContext() override { return Context; }
	ImPlotContext* GetImPlotContext() override { return PlotContext; }

	TObjectPtr<const UGameViewportClient> GetGameViewport() const override { return GameViewport; }
	TSharedPtr<const SCogImguiWidget> GetMainWidget() const override { return MainWidget; }
	
	bool GetEnableInput() const override { return bEnableInput; }
	void SetEnableInput(bool InValue) override;
	
	bool GetShareKeyboard() const override { return bShareKeyboard; }
	void SetShareKeyboard(bool Value) override { bShareKeyboard = Value; }
	
	bool GetShareMouse() const override { return bShareMouse; }
	void SetShareMouse(bool Value) override;
	
	void SetShareMouseWithGameplay(bool Value) override;
	bool GetShareMouseWithGameplay() const override { return bShareMouseWithGameplay; }
	
	ImVec2 GetImguiMousePos() const override;
	
	bool GetWantCaptureMouse() const override { return bWantCaptureMouse; }
	
	float GetDPIScale() const override { return DpiScale; }
	void SetDPIScale(float Value) override;

	bool GetSkipRendering() const override;
	void SetSkipRendering(bool Value) override;
	
	void Shutdown() override;
	void SaveSettings() const override;

	void OnImGuiWidgetFocusLost() override;
#pragma endregion ICogImguiContext

	void Initialize(UGameViewportClient* InGameViewport);

	static bool GetIsNetImguiInitialized() { return bIsNetImGuiInitialized; }

protected:

	friend struct FCogImGuiContextScope;

	void OnDisplayMetricsChanged(const FDisplayMetrics& DisplayMetrics) const;

	bool IsConsoleOpened() const;

	void DrawDebug() const;

	void BuildFont();

	void RefreshMouseCursor();

	ULocalPlayer* GetLocalPlayer() const;

	static void ImGui_CreateWindow(ImGuiViewport* Viewport);

	static void ImGui_DestroyWindow(ImGuiViewport* Viewport);

	static void ImGui_ShowWindow(ImGuiViewport* Viewport);

	static void ImGui_SetWindowPos(ImGuiViewport* Viewport, ImVec2 Pos);

	static ImVec2 ImGui_GetWindowPos(ImGuiViewport* Viewport);

	static void ImGui_SetWindowSize(ImGuiViewport* Viewport, ImVec2 Size);

	static ImVec2 ImGui_GetWindowSize(ImGuiViewport* Viewport);

	static void ImGui_SetWindowFocus(ImGuiViewport* Viewport);

	static bool ImGui_GetWindowFocus(ImGuiViewport* Viewport);

	static bool ImGui_GetWindowMinimized(ImGuiViewport* Viewport);

	static void ImGui_SetWindowTitle(ImGuiViewport* Viewport, const char* TitleAnsi);

	static void ImGui_SetWindowAlpha(ImGuiViewport* Viewport, float Alpha);

	static void ImGui_RenderWindow(ImGuiViewport* Viewport, void* Data);

	static const char* ImGui_GetClipboardTextFn(ImGuiContext* InImGuiContext);

	static void ImGui_SetClipboardTextFn(ImGuiContext* InImGuiContext, const char* Arg);

	static bool ImGui_OpenInShell(ImGuiContext* Context, const char* Path);

	UTexture2D* FontAtlasTexture = nullptr;

	TMap<TWeakPtr<SWindow>, ImGuiID> WindowToViewportMap;

	TSharedPtr<IInputProcessor> InputProcessor = nullptr;

	TStrongObjectPtr<UTexture2D> FontAtlasTexturePtr = nullptr;

	TSharedPtr<SCogImguiWidget> MainWidget = nullptr;

	TSharedPtr<SCogImguiInputCatcherWidget> InputCatcherWidget = nullptr;

	TWeakPtr<SWidget> PreviousMouseCaptor = nullptr;

	TObjectPtr<UGameViewportClient> GameViewport = nullptr;

	ImGuiContext* Context = nullptr;

	ImPlotContext* PlotContext = nullptr;

	char IniFilename[512] = {};

	TArray<char> ClipboardBuffer;
	
	bool bEnableInput = false;

	bool bShareMouse = false;

	bool bShareMouseWithGameplay = false;

	bool bHasSavedInitialCursorVisibility = false;

	bool bIsCursorInitiallyVisible = false;

	bool bShareKeyboard = false;

	bool bRefreshDPIScale = false;

	bool bIsThrottleDisabled = false;

	bool bIsFirstFrame = true;

	bool bWantCaptureMouse = false;

	float DpiScale = 1.f;

	bool bSkipRendering = false;

	bool bRetakeFocus = false;

	static bool bIsNetImGuiInitialized;
};
