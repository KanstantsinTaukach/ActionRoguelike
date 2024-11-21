// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "Weapon/ARMagicProjectile.h"
#include "Components/ARAttributeComponent.h"
#include "Components/SphereComponent.h"

AARMagicProjectile::AARMagicProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

    SphereComp->SetSphereRadius(20.0f);

    SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AARMagicProjectile::OnActorOverlap);  

    DamageAmount = 20.0f;
}

void AARMagicProjectile::OnActorOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                                        UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                        const FHitResult &SweepResult)
{
    if (OtherActor && OtherActor != GetInstigator())
    {
        const auto AttributeComp = Cast <UARAttributeComponent>(OtherActor->GetComponentByClass(UARAttributeComponent::StaticClass()));
        if (AttributeComp)
        {
            AttributeComp->ApplyHealthChange(-DamageAmount);

            // Only explode when we hit something valid
            Explode();
        }
    }
}