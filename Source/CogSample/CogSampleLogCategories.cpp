#include "CogSampleLogCategories.h"

#include "AbilitySystemLog.h"
#include "CogSampleDefines.h"

#if ENABLE_COG
#include "CogAIModule.h"
#include "CogDebugLog.h"
#include "CogImguiHelper.h"
#endif //ENABLE_COG

DEFINE_LOG_CATEGORY(LogCogAlways);

DEFINE_LOG_CATEGORY(LogCogAbility);
DEFINE_LOG_CATEGORY(LogCogArea);
DEFINE_LOG_CATEGORY(LogCogBaseAimRotation);
DEFINE_LOG_CATEGORY(LogCogCollision);
DEFINE_LOG_CATEGORY(LogCogControlRotation);
DEFINE_LOG_CATEGORY(LogCogInput);
DEFINE_LOG_CATEGORY(LogCogPosition);
DEFINE_LOG_CATEGORY(LogCogPossession);
DEFINE_LOG_CATEGORY(LogCogPredictedActor);
DEFINE_LOG_CATEGORY(LogCogProjectile);
DEFINE_LOG_CATEGORY(LogCogRotation);
DEFINE_LOG_CATEGORY(LogCogSkeleton);
DEFINE_LOG_CATEGORY(LogCogTargetAcquisition);

namespace CogSampleLog
{
    void RegisterAllLogCategories()
    {
#if ENABLE_COG
        
        FCogDebugLog::AddLogCategory(LogCogAlways, "Always", "Debug Category that is always active", false);

        FCogDebugLog::AddLogCategory(LogCogAbility, "Ability", "Log and debug draw of gameplay abilities");
        FCogDebugLog::AddLogCategory(LogCogArea, "Area", "Log and debug draw of area of effects");
        FCogDebugLog::AddLogCategory(LogCogAI, "AI", "Log and debug draw of AI behaviors");
        FCogDebugLog::AddLogCategory(LogAbilitySystem, "Ability System", "Unreal Ability System Log");
        FCogDebugLog::AddLogCategory(LogCogBaseAimRotation, "Base Aim Rotation", "Debug Draw of a Character BaseAimRotation");
        FCogDebugLog::AddLogCategory(LogCogCollision, "Collision", "Debug Draw a Character Collision");
        FCogDebugLog::AddLogCategory(LogCogControlRotation, "Control Rotation", "Debug Draw of the Character Control Rotation");
        FCogDebugLog::AddLogCategory(LogCogImGui, "ImGui", "Log related to imgui integration");
        FCogDebugLog::AddLogCategory(LogCogInput, "Input", "Log about the input actions");
        FCogDebugLog::AddLogCategory(LogCogPosition, "Position", "Debug draw of a character position");
        FCogDebugLog::AddLogCategory(LogCogPossession, "Possession", "Log about the possession of a PlayerController over a Character");
        FCogDebugLog::AddLogCategory(LogCogPredictedActor, "Predicted Actor", "Log and debug draw about the prediction of actors.");
        FCogDebugLog::AddLogCategory(LogCogProjectile, "Projectile", "Log and debug draw about the projectiles.");
        FCogDebugLog::AddLogCategory(LogCogRotation, "Rotation", "Debug Draw a Character Rotation");
        FCogDebugLog::AddLogCategory(LogCogSkeleton, "Skeleton", "Debug Draw a Character Skeleton");
        FCogDebugLog::AddLogCategory(LogCogTargetAcquisition, "Target Acquisition", "Debug Draw the target acquisition debug draw");
        FCogDebugLog::AddLogCategory(LogGameplayEffects, "Gameplay Effects", "Unreal Gameplay Effect Log");

#endif //ENABLE_COG
    }
}

