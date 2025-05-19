#pragma once

/*----------------------------------------------------------------------------
	Low level includes.
----------------------------------------------------------------------------*/

#include "CoreTypes.h"

/*----------------------------------------------------------------------------
	Forward declarations
----------------------------------------------------------------------------*/

#include "CoreFwd.h"
#include "UObject/UObjectHierarchyFwd.h"
#include "Containers/ContainersFwd.h"

/*----------------------------------------------------------------------------
	Commonly used headers
----------------------------------------------------------------------------*/

#include "Misc/VarArgs.h"
#include "Logging/LogVerbosity.h"
#include "UObject/ObjectMacros.h"
#include "Delegates/Delegate.h"
#include "Delegates/DelegateCombinations.h"

/*----------------------------------------------------------------------------*/

#include "CogEditorMinimal.generated.h"

#pragma region Engine Forwards
#pragma endregion Engine Forwards

#pragma region Cog Forwards
class UCogEditorModule;
class UCogEditorSubsystem;
#pragma endregion Cog Forwards


#pragma region Logging

// Straight from the Engine
UENUM(BlueprintType)
enum class ECogEditorVerbosity : uint8
{
	/** Not used */
	NoLogging		= 0,

	/** Always prints a fatal error to console (and log file) and crashes (even if logging is disabled) */
	// Fatal,
	// Just use GASA_Fatal...

	/** 
	 * Prints an error to console (and log file). 
	 * Commandlets and the editor collect and report errors. Error messages result in commandlet failure.
	 */
	Error = ELogVerbosity::Error,

	/** 
	 * Prints a warning to console (and log file).
	 * Commandlets and the editor collect and report warnings. Warnings can be treated as an error.
	 */
	Warning,

	/** Prints a message to console (and log file) */
	Display,

	/** Prints a message to a log file (does not print to console) */
	Log,

	/** 
	 * Prints a verbose message to a log file (if Verbose logging is enabled for the given category, 
	 * usually used for detailed logging) 
	 */
	Verbose,

	/** 
	 * Prints a verbose message to a log file (if VeryVerbose logging is enabled, 
	 * usually used for detailed logging that would otherwise spam output) 
	 */
	VeryVerbose,
};

DECLARE_LOG_CATEGORY_EXTERN(LogCogEditor, Log, All);

namespace CogEditor
{
	using ELogV = ECogEditorVerbosity;

	// Works for Unreal 5.4, Win64 MSVC (untested in other scenarios, for now)
	inline
	void Log( FString Message
		, ELogV             Verbosity = ELogV::Log
		, FLogCategoryBase& Category  = LogCogEditor
		, bool              DumpStack = false
		, int32             Line      = __builtin_LINE()
		, const ANSICHAR*   File      = __builtin_FILE()
		, const ANSICHAR*   Func      = __builtin_FUNCTION() )
	{
	#if !UE_BUILD_SHIPPING && !NO_LOGGING
		ELogVerbosity::Type EngineVerbosity = (ELogVerbosity::Type) Verbosity;

		static UE::Logging::Private::FStaticBasicLogDynamicData LOG_Dynamic;
		static UE::Logging::Private::FStaticBasicLogRecord
		LOG_Static(TEXT("%s -- %hs %hs(%d)"), File, Line, EngineVerbosity, LOG_Dynamic);

		if ((EngineVerbosity & ELogVerbosity::VerbosityMask) <= ELogVerbosity::COMPILED_IN_MINIMUM_VERBOSITY)
		{
			if ((EngineVerbosity & ELogVerbosity::VerbosityMask) <= Category.GetVerbosity())
			{
				if ( ! Category.IsSuppressed(EngineVerbosity))
				{
					if (DumpStack)
						FDebug::DumpStackTraceToLog(EngineVerbosity);
					BasicLog(Category, &LOG_Static, *Message, File, Func, Line);
				}
			}
		}
	#endif
	}
}

#define CogEditor_Fatal(Message)       UE_LOG( LogCogEditor, Fatal,       TEXT("%s -- %hs %hs(%d)"), *Message, __builtin_FILE(), __func__, __builtin_LINE()  );
#define CogEditor_Error(Message)       UE_LOG( LogCogEditor, Error,       TEXT("%s -- %hs %hs(%d)"), *Message, __builtin_File(), __func__, __builtin_LINE()  );
#define CogEditor_Warning(Message)     UE_LOG( LogCogEditor, Warning,     TEXT("%s -- %hs %hs(%d)"), *Message, __builtin_File(), __func__, __builtin_LINE()  );
#define CogEditor_Display(Message)     UE_LOG( LogCogEditor, Display,     TEXT("%s -- %hs %hs(%d)"), *Message, __builtin_File(), __func__, __builtin_LINE()  );
#define CogEditor_Log(Message)         UE_LOG( LogCogEditor, Log,         TEXT("%s -- %hs %hs(%d)"), *Message, __builtin_File(), __func__, __builtin_LINE()  );
#define CogEditor_Verbose(Message)     UE_LOG( LogCogEditor, Verbose,     TEXT("%s -- %hs %hs(%d)"), *Message, __builtin_File(), __func__, __builtin_LINE()  );
#define CogEditor_VeryVerbose(Message) UE_LOG( LogCogEditor, VeryVerbose, TEXT("%s -- %hs %hs(%d)"), *Message, __builtin_File(), __func__, __builtin_LINE()  );
#pragma endregion Logging
