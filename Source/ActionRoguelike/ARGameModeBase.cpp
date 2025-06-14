// Copyright Epic Games, Inc. All Rights Reserved.

#include "ARGameModeBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery//EnvQueryInstanceBlueprintWrapper.h"
#include "AI/ARAICharacter.h"
#include "Components/ARAttributeComponent.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "Player/ARCharacter.h"
#include "Player/ARPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(ARGameModeBaseLog, All, All);

static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("ar.SpawnBots"), true, TEXT("Enable spawning of bots via timer."), ECVF_Cheat);

AARGameModeBase::AARGameModeBase()
{
    PlayerStateClass = AARPlayerState::StaticClass();

    SpawnTimerInterval = 2.0f;

    CreditsPerKill = 30;

    DesiredPowerupCount = 10;
    RequiredPowerupDistance = 3000.0f;
}

void AARGameModeBase::StartPlay()
{
    Super::StartPlay();

    GetWorldTimerManager().SetTimer(SpawnBotsTimerHandle, this, &AARGameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);

    // Make sure we have assigned at least one power-up class
    if(ensure(PowerupClasses.Num() > 0))
    {
        // Run EQS to find potential power-up locations
        UEnvQueryInstanceBlueprintWrapper* QueryInstance =
            UEnvQueryManager::RunEQSQuery(this, PowerupSpawnQuery, this, EEnvQueryRunMode::AllMatching, nullptr);

        if(ensure(QueryInstance))
        {
            QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AARGameModeBase::OnPowerupSpawnQueryCompleted);
        }
    }
}

void AARGameModeBase::SpawnBotTimerElapsed()
{
    if (!CVarSpawnBots.GetValueOnGameThread())
    {
        UE_LOG(ARGameModeBaseLog, Warning, TEXT("Bot spawning disbled via cvar 'CVarSpawnBots'."));
        return;
    }

    int32 NumOfAliveBots = 0;
    for (TActorIterator<AARAICharacter> It(GetWorld()); It; ++It)
    {
        const auto Bot = *It;

        const auto AttributeComponent = UARAttributeComponent::GetAttributes(Bot);
        if (ensure(AttributeComponent) && AttributeComponent->IsAlive())
        {
            ++NumOfAliveBots;
        }
    }

    UE_LOG(ARGameModeBaseLog, Log, TEXT("Found %i alive bots."), NumOfAliveBots);

    float MaxBotCount = 15.0f;
    if (DifficultyCurve)
    {
        MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
    }

    if (NumOfAliveBots >= MaxBotCount)
    {
        UE_LOG(ARGameModeBaseLog, Log, TEXT("At maximum bot capacity. Skipping bot spawn."));

        return;
    }

    const auto QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
    if (ensure(QueryInstance))
    {
        QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AARGameModeBase::OnBotSpawnQueryCompleted);
    }    
}

void AARGameModeBase::OnBotSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper *QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
    if (QueryStatus != EEnvQueryStatus::Success)
    {
        UE_LOG(ARGameModeBaseLog, Warning, TEXT("Spawn bot EQS Query failed!"));
        return;
    }  

    TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

    if (GetWorld() && Locations.IsValidIndex(0))
    {
        GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);

        DrawDebugSphere(GetWorld(), Locations[0], 50.0f, 16, FColor::Blue, false, 100.0f);
    }
}

void AARGameModeBase::OnPowerupSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus) 
{
    if(QueryStatus != EEnvQueryStatus::Success)
    {
        UE_LOG(ARGameModeBaseLog, Warning, TEXT("Spawn power-up EQS Query failed!"));
        return;
    }

    TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

    // Keep used locations to easily check distance between points
    TArray<FVector> UsedLocations;

    int32 SpawnCounter = 0;

    // Break out if we reached the desired count or if we have no more potential positions remaining
    while(SpawnCounter < DesiredPowerupCount && Locations.Num() > 0)
    {
        // Pick a random location from remaining points
        int32 RandomLocationIndex = FMath::RandRange(0, Locations.Num() - 1);

        FVector PickedLocation = Locations[RandomLocationIndex];
        // Remove to avoid picking again
        Locations.RemoveAt(RandomLocationIndex);

        // Check minimum distance requerement
        bool bValidLocation = true;
        for(FVector OtherLocation : UsedLocations)
        {
            float DistanceTo = (PickedLocation - OtherLocation).Size();

            if(DistanceTo < RequiredPowerupDistance)
            {
                // Show skipped locations due to distance
                if(GetWorld()) DrawDebugSphere(GetWorld(), PickedLocation, 50.0f, 20, FColor::Red, false, 10.0f);

                // too close, skip to next attempt
                bValidLocation = false;
                break;
            }
        }

        // Failed the distance test
        if(!bValidLocation)
        {
            continue;
        }

        // Pick a random powerup-class
        int32 RandomClassIndex = FMath::RandRange(0, PowerupClasses.Num() - 1);
        TSubclassOf<AActor> RandomPowerupClass = PowerupClasses[RandomClassIndex];

        if(GetWorld())
        {
            GetWorld()->SpawnActor<AActor>(RandomPowerupClass, PickedLocation, FRotator::ZeroRotator);

            // Keep for distance checks
            UsedLocations.Add(PickedLocation);
            SpawnCounter++;
        }

    }
}

void AARGameModeBase::KillAll()
{
    for (TActorIterator<AARAICharacter> It(GetWorld()); It; ++It)
    {
        const auto Bot = *It;

        const auto AttributeComponent = UARAttributeComponent::GetAttributes(Bot);
        if (ensure(AttributeComponent) && AttributeComponent->IsAlive())
        {
            AttributeComponent->Kill(this);
        }
    }
}

void AARGameModeBase::OnActorKilled(AActor *VictimActor, AActor *Killer)
{
    const auto Player = Cast<AARCharacter>(VictimActor);
    if (Player)
    {
        FTimerHandle TimerHandle_RespawnDelay;

        FTimerDelegate Delegate;
        Delegate.BindUFunction(this, "RespawnPlayerElapsed", Player->GetController());

        float RespawnDelay = 3.0f;
        GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, Delegate, RespawnDelay, false);
    }

    const auto KillerPawn = Cast<APawn>(Killer);
    if(KillerPawn)
    {
        const auto PS = KillerPawn->GetPlayerState<AARPlayerState>();
        if(PS)
        {
            PS->AddCredits(CreditsPerKill);
        }
    }

    UE_LOG(ARGameModeBaseLog, Log, TEXT("OnActorKilled: Victim: %s, Killer: %s"), *GetNameSafe(VictimActor), *GetNameSafe(Killer));
}

void AARGameModeBase::RespawnPlayerElapsed(AController* Controller)
{
    if (ensure(Controller))
    {
        Controller->UnPossess();
        RestartPlayer(Controller);
    }
}