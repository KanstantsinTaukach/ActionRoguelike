// Copyright Epic Games, Inc. All Rights Reserved.

#include "ARGameModeBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery//EnvQueryInstanceBlueprintWrapper.h"
#include "AI/ARAICharacter.h"
#include "Components/ARAttributeComponent.h"
#include "EngineUtils.h"

DEFINE_LOG_CATEGORY_STATIC(ARGameModeBaseLog, All, All);

ARGameModeBase::ARGameModeBase()
{
    SpawnTimerInterval = 2.0f;
}

void ARGameModeBase::StartPlay()
{
    Super::StartPlay();

    GetWorldTimerManager().SetTimer(SpawnBotsTimerHandle, this, &ARGameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);
}

void ARGameModeBase::SpawnBotTimerElapsed()
{
    const auto QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);

    if (ensure(QueryInstance))
    {
        QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ARGameModeBase::OnQueryCompleted);
    }    
}

void ARGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper *QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
    if (QueryStatus != EEnvQueryStatus::Success)
    {
        UE_LOG(ARGameModeBaseLog, Warning, TEXT("Spawn bot EQS Query failed!"));
        return;
    }

    int32 NumOfAliveBots = 0;
    for (TActorIterator<AARAICharacter> It(GetWorld()); It; ++It)
    {
        const auto Bot = *It;

        const auto AttributeComponent = Cast<UARAttributeComponent>(Bot->GetComponentByClass(UARAttributeComponent::StaticClass()));
        if (AttributeComponent && AttributeComponent->IsAlive())
        {
            ++NumOfAliveBots;
        }
    }

    float MaxBotCount;

    if (DifficultyCurve)
    {
        MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
    }

    if (NumOfAliveBots >= MaxBotCount)
    {
        return;
    }

    TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

    if (Locations.IsValidIndex(0))
    {
        GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);
    }
}