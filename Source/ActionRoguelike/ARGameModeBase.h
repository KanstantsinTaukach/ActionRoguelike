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
    float SpawnTimerInterval;

    UPROPERTY(EditDefaultsOnly, Category = "AI")
    UEnvQuery *SpawnBotQuery;

    UPROPERTY(EditDefaultsOnly, Category = "AI")
    TSubclassOf<AActor> MinionClass;

    UPROPERTY(EditDefaultsOnly, Category = "AI")
    UCurveFloat *DifficultyCurve;

    UFUNCTION()
    void SpawnBotTimerElapsed();

    UFUNCTION()
    void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper *QueryInstance, EEnvQueryStatus::Type QueryStatus);

    UFUNCTION()
    void RespawnPlayerElapsed(AController *Controller);
};
