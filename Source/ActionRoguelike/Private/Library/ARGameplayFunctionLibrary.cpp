// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.


#include "Library/ARGameplayFunctionLibrary.h"
#include "Components/ARAttributeComponent.h"

bool UARGameplayFunctionLibrary::ApplyDamage(AActor *DamageCauser, AActor *TargetActor, float DamageAmount)
{
    const auto AttributeComponent = UARAttributeComponent::GetAttributes(TargetActor);
    if (AttributeComponent)
    {
        return AttributeComponent->ApplyHealthChange(DamageCauser, -DamageAmount);
    }
    return false;
}

bool UARGameplayFunctionLibrary::ApplyDirectionalDamage(AActor *DamageCauser, AActor *TargetActor, float DamageAmount, const FHitResult &HitResult)
{
    if (ApplyDamage(DamageCauser, TargetActor, DamageAmount))
    {
        UPrimitiveComponent* HitComp = HitResult.GetComponent();
        if (HitComp && HitComp->IsSimulatingPhysics(HitResult.BoneName))
        {
            // Direction = Target - Origin
            FVector Direction = HitResult.TraceEnd - HitResult.TraceStart;
            Direction.Normalize();

            float ImpulsePower = 300000.0f;

            HitComp->AddImpulseAtLocation(Direction * ImpulsePower, HitResult.ImpactPoint, HitResult.BoneName);
        }

        return true;
    }

    return false;
}
