// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "PowerUps/ARBasePowerup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

AARBasePowerup::AARBasePowerup()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->SetCollisionProfileName("Powerup");
    RootComponent = CollisionComponent;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    MeshComponent->SetupAttachment(RootComponent);

    RespawnTime = 10.0f;

    SetReplicates(true);
}

void AARBasePowerup::BeginPlay()
{
    Super::BeginPlay();

    check(CollisionComponent);
}

void AARBasePowerup::ShowPowerup()
{
    SetPowerupState(true);
}

void AARBasePowerup::HideAndCooldownPowerup()
{
    SetPowerupState(false);

    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AARBasePowerup::ShowPowerup, RespawnTime);
}

void AARBasePowerup::SetPowerupState(bool bNewIsActive)
{
    SetActorEnableCollision(bNewIsActive);

    RootComponent->SetVisibility(bNewIsActive, true);
}

void AARBasePowerup::Interact_Implementation(APawn *InstigatorPawn)
{
}