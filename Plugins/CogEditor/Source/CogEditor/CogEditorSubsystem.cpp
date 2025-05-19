#include "CogEditorSubsystem.h"

#include "Editor.h"

#include "imgui_internal.h"

#include "CogConsoleCommandManager.h"
#include "CogWindow_Spacing.h"
#include "CogWindow_Layouts.h"
#include "CogWindow_Settings.h"

FString UCogEditorSubsystem::ToggleInputCommand   = TEXT("CogEditor.ToggleInput");
FString UCogEditorSubsystem::DisableInputCommand  = TEXT("CogEditor.DisableInput");
FString UCogEditorSubsystem::LoadLayoutCommand    = TEXT("CogEditor.LoadLayout");
FString UCogEditorSubsystem::SaveLayoutCommand    = TEXT("CogEditor.SaveLayout");
FString UCogEditorSubsystem::ResetLayoutCommand   = TEXT("CogEditor.ResetLayout");

UE_DISABLE_OPTIMIZATION
ETickableTickType UCogEditorSubsystem::GetTickableTickType() const
{
	return ETickableTickType::Never;
}
UE_ENABLE_OPTIMIZATION

void UCogEditorSubsystem::TryInitialize(UWorld& World)
{
	// Super::TryInitialize(World);
	
    if (bIsInitialized) {
	    return;
    }

    // FWorldContext* WorldContext = GEngine->GetWorldContextFromWorld(&World);
    // if (WorldContext == nullptr) {
	   //  return;
    // }

    // if (WorldContext->GameViewport == nullptr && IsRunningDedicatedServer() == false) {
	   //  return;
    // }

	FWorldContext& WorldContext = GEditor->GetEditorWorldContext(false);

	using namespace CogEditor;
	
	Log(FString::Printf(TEXT("UCogSubsystem::TryInitialize | World:%s %p"), *World.GetName(), &World), ELogV::Verbose);

	Context = MakeUnique<FCogEditorImguiContext>();
	FCogEditorImguiContext& EditorCtx = *(FCogEditorImguiContext*)(Context.Get());
	EditorCtx.Initialize();

    FCogImGuiContextScope ImGuiContextScope(* Context);
    
    ImGuiSettingsHandler IniHandler;
    IniHandler.TypeName = "CogEditor";
    IniHandler.TypeHash = ImHashStr("CogEditor");
    IniHandler.ClearAllFn = SettingsHandler_ClearAll;
    IniHandler.ReadOpenFn = SettingsHandler_ReadOpen;
    IniHandler.ReadLineFn = SettingsHandler_ReadLine;
    IniHandler.ApplyAllFn = SettingsHandler_ApplyAll;
    IniHandler.WriteAllFn = SettingsHandler_WriteAll;
    IniHandler.UserData = this;
    ImGui::AddSettingsHandler(&IniHandler);
    
    SpaceWindows.Add(AddWindow<FCogWindow_Spacing>("Spacing 1"));
    SpaceWindows.Add(AddWindow<FCogWindow_Spacing>("Spacing 2"));
    SpaceWindows.Add(AddWindow<FCogWindow_Spacing>("Spacing 3"));
    SpaceWindows.Add(AddWindow<FCogWindow_Spacing>("Spacing 4"));
    
	Settings = GetConfig<UCogWindowConfig_Settings>();
    
    UCogWindowConfig_Settings* SettingsPtr = Settings.Get();
    AddShortcut(SettingsPtr, &UCogWindowConfig_Settings::Shortcut_ToggleImguiInput).BindLambda([this] () { ToggleInputMode(); });
    AddShortcut(SettingsPtr, &UCogWindowConfig_Settings::Shortcut_LoadLayout1).BindLambda([this] (){ LoadLayout(1); });
    AddShortcut(SettingsPtr, &UCogWindowConfig_Settings::Shortcut_LoadLayout2).BindLambda([this] (){ LoadLayout(2); });
    AddShortcut(SettingsPtr, &UCogWindowConfig_Settings::Shortcut_LoadLayout3).BindLambda([this] (){ LoadLayout(3); });
    AddShortcut(SettingsPtr, &UCogWindowConfig_Settings::Shortcut_LoadLayout4).BindLambda([this] (){ LoadLayout(4); });
    AddShortcut(SettingsPtr, &UCogWindowConfig_Settings::Shortcut_SaveLayout1).BindLambda([this] (){ SaveLayout(1); });
    AddShortcut(SettingsPtr, &UCogWindowConfig_Settings::Shortcut_SaveLayout2).BindLambda([this] (){ SaveLayout(2); });
    AddShortcut(SettingsPtr, &UCogWindowConfig_Settings::Shortcut_SaveLayout3).BindLambda([this] (){ SaveLayout(3); });
    AddShortcut(SettingsPtr, &UCogWindowConfig_Settings::Shortcut_SaveLayout4).BindLambda([this] (){ SaveLayout(4); });    
    AddShortcut(SettingsPtr, &UCogWindowConfig_Settings::Shortcut_ResetLayout).BindLambda([this] (){ ResetLayout(); });
    
     LayoutsWindow = AddWindow<FCogWindow_Layouts>("Window.Layouts");
     SettingsWindow = AddWindow<FCogWindow_Settings>("Window.Settings");

    for (FCogWindow* Window : Windows)
    {
        InitializeWindow(Window);   
    }
    
    FCogConsoleCommandManager::RegisterWorldConsoleCommand(
        *ToggleInputCommand, 
        TEXT("Toggle the input focus between the Game and ImGui"),
        GetWorld(),
        FCogWindowConsoleCommandDelegate::CreateLambda([this](const TArray<FString>& InArgs, UWorld* InWorld)
        {
            ToggleInputMode();
        }));
    
    FCogConsoleCommandManager::RegisterWorldConsoleCommand(
        *DisableInputCommand,
        TEXT("Disable ImGui input"), 
        GetWorld(),
        FCogWindowConsoleCommandDelegate::CreateLambda([this](const TArray<FString>& InArgs, UWorld* InWorld)
        {
            DisableInputMode();
        }));
    
    FCogConsoleCommandManager::RegisterWorldConsoleCommand(
        *ResetLayoutCommand,
        TEXT("Reset the layout."),
        GetWorld(),
        FCogWindowConsoleCommandDelegate::CreateLambda([this](const TArray<FString>& InArgs, UWorld* InWorld)
        {
            if (InArgs.Num() > 0)
            {
                ResetLayout();
            }
        }));
    
    FCogConsoleCommandManager::RegisterWorldConsoleCommand(
        *LoadLayoutCommand,
        TEXT("Load the layout. CogEditor.LoadLayout <Index>"),
        GetWorld(),
        FCogWindowConsoleCommandDelegate::CreateLambda([this](const TArray<FString>& InArgs, UWorld* InWorld)
        {
            if (InArgs.Num() > 0)
            {
                LoadLayout(FCString::Atoi(*InArgs[0]));
            }
        }));
    
    FCogConsoleCommandManager::RegisterWorldConsoleCommand(
        *SaveLayoutCommand,
        TEXT("Save the layout. CogEditor.SaveLayout <Index>"),
        GetWorld(),
        FCogWindowConsoleCommandDelegate::CreateLambda([this](const TArray<FString>& InArgs, UWorld* InWorld)
        {
            if (InArgs.Num() > 0)
            {
                SaveLayout(FCString::Atoi(*InArgs[0]));
            }
        }));


    bIsInitialized = true;	
}

UE_DISABLE_OPTIMIZATION
bool UCogEditorSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	bool bIsEditorWorld = GetWorld() == GEditor->EditorWorld;
	bool bParentCreate =  Super::ShouldCreateSubsystem(Outer);
	return bParentCreate && bIsEditorWorld;
}
UE_ENABLE_OPTIMIZATION

bool UCogEditorSubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Editor;
}

bool UCogEditorSubsystem::EditorTick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	return true;
}

void UCogEditorSubsystem::PostInitialize()
{
	Super::PostInitialize();

	TickerDelegate       = FTickerDelegate::CreateUObject(this, &UCogEditorSubsystem::EditorTick);
	TickerDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(TickerDelegate);
}

void UCogEditorSubsystem::Deinitialize()
{
	Super::Deinitialize();
	FTSTicker::GetCoreTicker().RemoveTicker(TickerDelegateHandle);
}
