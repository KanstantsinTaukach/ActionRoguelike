// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "ARGameModeBase.generated.h"

class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;
class UCurveFloat;

UCLASS()
class ACTIONROGUELIKE_API AARGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

  public:
    AARGameModeBase();

    virtual void StartPlay() override;

    UFUNCTION(Exec)
    void KillAll();

    virtual void OnActorKilled(AActor *VictimActor, AActor *Killer);

  protected:
    FTimerHandle SpawnBotsTimerHandle;

    UPROPERTY(EditDefaultsOnly, Category = "AI")
    TSubclassOf<AActor> MinionClass;

    UPROPERTY(EditDefaultsOnly, Category = "AI")
    UEnvQuery *SpawnBotQuery;

    UPROPERTY(EditDefaultsOnly, Category = "AI")
    UCurveFloat *DifficultyCurve;

    UPROPERTY(EditDefaultsOnly, Category = "AI")
    float SpawnTimerInterval;

    // Read/write access as we could change this as our difficulty increases via Blueprint
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    int32 CreditsPerKill;

    UPROPERTY(EditDefaultsOnly, Category = "Powerups")
    UEnvQuery* PowerupSpawnQuery;

    // All power-up classes used to spawn with EQS at match start
    UPROPERTY(EditDefaultsOnly, Category = "Powerups")
    TArray<TSubclassOf<AActor>> PowerupClasses;

    // Distance required between puwer-up spawn locations
    UPROPERTY(EditDefaultsOnly, Category = "Powerups")
    float RequiredPowerupDistance;

    // Amount of powerups to spawn during match start
    UPROPERTY(EditDefaultsOnly, Category = "Powerups")
    int32 DesiredPowerupCount;

    UFUNCTION()
    void SpawnBotTimerElapsed();

    UFUNCTION()
    void OnBotSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper *QueryInstance, EEnvQueryStatus::Type QueryStatus);

    UFUNCTION()
    void OnPowerupSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

    UFUNCTION()
    void RespawnPlayerElapsed(AController *Controller);
};
