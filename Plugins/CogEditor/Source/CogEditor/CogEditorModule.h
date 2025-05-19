#pragma once

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

#include "CogEditorMinimal.h"

class COGEDITOR_API FCogEditorModule : public IModuleInterface
{
public:
	static FCogEditorModule& Get() { return FModuleManager::LoadModuleChecked<FCogEditorModule>("CogEditor"); }

	void StartupModule() override;
	void ShutdownModule() override;	
};

