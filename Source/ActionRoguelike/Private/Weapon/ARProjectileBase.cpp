// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.


#include "Weapon/ARProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

AARProjectileBase::AARProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
    SphereComp->SetCollisionProfileName("Projectile");
    SphereComp->OnComponentHit.AddDynamic(this, &AARProjectileBase::OnActorHit);
    RootComponent = SphereComp;

    EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
    EffectComp->SetupAttachment(SphereComp);

    MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp");
    MovementComp->InitialSpeed = 8000.0f;
    MovementComp->bRotationFollowsVelocity = true;
    MovementComp->bInitialVelocityInLocalSpace = true;
    MovementComp->ProjectileGravityScale = 0.0f;
}

void AARProjectileBase::OnActorHit(UPrimitiveComponent *HitComponent, AActor *OtherActor,
                                   UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
    Explode();
}

// _Implementation from it being marked as BlueprintNativeEvent
void AARProjectileBase::Explode_Implementation()
{
    // Check to make sure we aren't already being 'destroyed'
    // Adding ensure to see if we encounter this situation at all
    if (ensure(!IsPendingKill()))
    {
        UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

        Destroy();
    }
}

void AARProjectileBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    // SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
}
