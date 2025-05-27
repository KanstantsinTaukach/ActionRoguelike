// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "Weapon/ARMagicProjectile.h"
#include "Components/ARAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "Library/ARGameplayFunctionLibrary.h"

AARMagicProjectile::AARMagicProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

    SphereComp->SetSphereRadius(20.0f);
    SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);

    SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AARMagicProjectile::OnActorOverlap);  

    DamageAmount = 20.0f;
}

void AARMagicProjectile::OnActorOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                                        UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                        const FHitResult &SweepResult)
{
    if (OtherActor && OtherActor != GetInstigator())
    {
        if (UARGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, DamageAmount, SweepResult))
        {
            Explode();
        }
    }
}