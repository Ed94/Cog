using UnrealBuildTool;

public class CogEditor : ModuleRules
{
	public CogEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		bUseUnity           = false;
		bMergeUnityFiles    = false;
		IWYUSupport         = IWYUSupport.None;
		PCHUsage            = PCHUsageMode.NoPCHs;
		OptimizeCode        = CodeOptimization.Never;
		MinCpuArchX64       = MinimumCpuArchitectureX64.AVX512;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		bCodeCoverage                   = false;
		bDisableStaticAnalysis          = true;
		bValidateCircularDependencies   = true;
		bValidateFormatStrings          = false;
		bValidateInternalApi            = false;
		bEnableExceptions               = false;
		bEnableBufferSecurityChecks     = false;
		bEnableNonInlinedGenCppWarnings = false;
		bIgnoreUnresolvedSymbols        = false;
		// bEnableUndefinedIdentifierWarnings = false;

		bWarningsAsErrors               = false;
		ShadowVariableWarningLevel      = UnrealBuildTool.WarningLevel.Off;
		UndefinedIdentifierWarningLevel = UnrealBuildTool.WarningLevel.Off;

		UndefinedIdentifierWarningLevel = WarningLevel.Off;

		bEnableObjCAutomaticReferenceCounting = false;
		bEnableObjCExceptions                 = false;

		var Kilobyte = 1024;
		NumIncludedBytesPerUnityCPPOverride    = Kilobyte * 32;
		MinFilesUsingPrecompiledHeaderOverride = 1;

		#region Engine
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"CoreUObject",
			"Engine",
			
			"Slate",
			"SlateCore",
			
			"UnrealEd"
		});
		#endregion Engine


		#region Cog
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"Cog",
			"CogCommon",
			"CogImgui",
			"CogDebug",
		});
		#endregion Cog
	}
}