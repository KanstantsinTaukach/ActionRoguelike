// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "Weapon/ARDashProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "particles/ParticleSystemComponent.h"

AARDashProjectile::AARDashProjectile()
{
    TeleportDelay = 0.2f;
    DetonateDelay = 0.2f;

    MovementComp->InitialSpeed = 6000.0f;
}

void AARDashProjectile::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &AARDashProjectile::Explode, DetonateDelay);
}

void AARDashProjectile::Explode_Implementation()
{
    // Clear timer if the Explode was already called through another source like OnActorHit
    GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);

    UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

    EffectComp->DeactivateSystem();

    MovementComp->StopMovementImmediately();
    SetActorEnableCollision(false);

    FTimerHandle TimerHandle_DelayedTeleport;
    GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &AARDashProjectile::TeleportInstigator,
                                    TeleportDelay);

    // Skip base implementation as it will destory actor (we need to stay alive a bit longer to finish the 2nd timer
    // Super::Explode_Implementation();
}

void AARDashProjectile::TeleportInstigator()
{
    AActor *ActorToTeleport = GetInstigator();
    if (ensure(ActorToTeleport))
    {
        // Keep instigator rotation or it may end up jarring
        ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);
    }
}
