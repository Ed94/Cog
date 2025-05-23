#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Ability_Activation_Fail_Cooldown);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Ability_Activation_Fail_Cost);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Ability_Cooldown);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Ability_Cooldown_1);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Ability_Cooldown_2);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Ability_Cooldown_3);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Ability_Cooldown_4);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Ability_Cooldown_5);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Ability_Cooldown_6);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Ability_Cooldown_7);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Ability_Cooldown_8);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Ability_Type_Active);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Ability_Type_Passive);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Ability_Type_Hidden);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Effect_Alignment_Negative);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Effect_Alignment_Positive);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Effect_Data_Amount);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Effect_Data_Cooldown);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Effect_Data_Cost);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Effect_Data_Damage);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Effect_Data_Heal);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Effect_Type_Cost_Overtime);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Effect_Type_Cost_Stamina);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Effect_Type_Damage_Kill);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Effect_Type_Heal_Full);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Effect_Type_Heal_Revive);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Effect_Type_Hidden);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_GameplayCue_DamageReceived);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Status_Dead);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Status_Ghost);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Status_Immobilized);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Status_Immune_Damage);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Status_Invisible);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Status_NoCooldown);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Status_NoCost);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Status_Revived);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Status_Silenced);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Status_Stunned);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_GameplayEvent_Killed);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_GameplayEvent_Revived);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_MontageEvent_Cast_Begin);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_MontageEvent_Cast_End);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Unit_Hero);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Unit_Creature);

struct UCogSampleFunctionLibrary_Tag
{
public:

    static TArray<FGameplayTag> ActiveAbilityCooldownTags;
};