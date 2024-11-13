// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "Weapon/ARMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "Components/ARAttributeComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

AARMagicProjectile::AARMagicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
    SphereComp->SetCollisionProfileName("Projectile");
    SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AARMagicProjectile::OnActorOverlap);
    RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
    EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
    MovementComp->InitialSpeed = 1000.0f;
    MovementComp->bRotationFollowsVelocity = true;
    MovementComp->bInitialVelocityInLocalSpace = true;
}

void AARMagicProjectile::OnActorOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                                        UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                        const FHitResult &SweepResult)
{
    if (OtherActor)
    {
        const auto AttributeComp = Cast <UARAttributeComponent>(OtherActor->GetComponentByClass(UARAttributeComponent::StaticClass()));
        if (AttributeComp)
        {
            AttributeComp->ApplyHealthChange(-20.0f);

            Destroy();
        }
    }
}

void AARMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AARMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
