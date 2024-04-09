#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/EngineTypes.h"
#include "CogEngineDataAsset.generated.h"

//--------------------------------------------------------------------------------------------------------------------------
USTRUCT()
struct COGENGINE_API FCogEngineSpawnEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category="Cog")
    TSubclassOf<AActor> Class;

    UPROPERTY(EditAnywhere, Category="Cog")
    TObjectPtr<const UObject> Asset = nullptr;
};

//--------------------------------------------------------------------------------------------------------------------------
USTRUCT()
struct COGENGINE_API FCogEngineSpawnGroup
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category="Cog")
    FString Name;

    UPROPERTY(EditAnywhere, Category="Cog")
    FLinearColor Color = FLinearColor(0.5f, 0.5f, 0.5f, 1.0f);

    UPROPERTY(EditAnywhere, Category="Cog")
    TArray<FCogEngineSpawnEntry> Spawns;
};

//--------------------------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable)
class COGENGINE_API UCogEngineDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    
    UCogEngineDataAsset() {}

    UPROPERTY(Category = "Spawns", EditAnywhere, meta = (TitleProperty = "Name"))
    TArray<FCogEngineSpawnGroup> SpawnGroups;
};
