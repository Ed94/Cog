#pragma once

#include "CogEditorImguiContext.h"
#include "CogEditorMinimal.h"
#include "CogSubsystem.h"
#include "Containers/Ticker.h"

#include "CogEditorSubsystem.generated.h"

UCLASS()
class COGEDITOR_API UCogEditorSubsystem : public UCogSubsystem
{
	GENERATED_BODY()
public:

	ETickableTickType GetTickableTickType() const override;

	void TryInitialize(UWorld& World) override;

	bool ShouldCreateSubsystem(UObject* Outer) const override;

	bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	bool EditorTick(float DeltaTime);

	void PostInitialize() override;
	void Deinitialize() override;

	FTickerDelegate TickerDelegate;
	FTSTicker::FDelegateHandle TickerDelegateHandle;

	static FString EnableCommand;
	static FString ToggleInputCommand;
	static FString DisableInputCommand;
	static FString LoadLayoutCommand;
	static FString SaveLayoutCommand;
	static FString ResetLayoutCommand;
};
