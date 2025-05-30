// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "Weapon/ARMagicProjectile.h"
#include "Components/ARAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "Components/ARActionComponent.h"
#include "Library/ARGameplayFunctionLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"

AARMagicProjectile::AARMagicProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    SphereComp->SetSphereRadius(20.0f);
    SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);

    SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AARMagicProjectile::OnActorOverlap);

    DamageAmount = 20.0f;
}

void AARMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != GetInstigator())
    {
        //static FGameplayTag Tag = FGameplayTag::RequestGameplayTag("Status.Parrying");

        const auto ActionComp = Cast<UARActionComponent>(OtherActor->GetComponentByClass(UARActionComponent::StaticClass()));
        if (ActionComp && ActionComp->ActiveGameplayTags.HasTag(ParryTag))
        {
            if (MovementComp)
            {
                MovementComp->Velocity = -MovementComp->Velocity;
            }

            SetInstigator(Cast<APawn>(OtherActor));
            return;
        }

        if (UARGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, DamageAmount, SweepResult))
        {
            Explode();
        }
    }
}