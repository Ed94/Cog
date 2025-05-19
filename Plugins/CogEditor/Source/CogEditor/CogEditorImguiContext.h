#pragma once

#include "CogImguiContext.h"

class COGEDITOR_API FCogEditorImguiContext : public FCogImguiContext
{
public:

	void Initialize(UGameViewportClient* viewport) = delete;
	void Initialize();
};
