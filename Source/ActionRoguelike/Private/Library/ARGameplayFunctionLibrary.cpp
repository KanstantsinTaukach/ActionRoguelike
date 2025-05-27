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
            HitComp->AddImpulseAtLocation(-HitResult.ImpactNormal * 300000.0f, HitResult.ImpactPoint, HitResult.BoneName);
        }

        return true;
    }

    return false;
}
