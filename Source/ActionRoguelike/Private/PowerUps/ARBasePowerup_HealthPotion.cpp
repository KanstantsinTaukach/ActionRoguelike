// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "PowerUps/ARBasePowerup_HealthPotion.h"
#include "ARAttributeComponent.h"
#include "Player/ARPlayerState.h"

AARBasePowerup_HealthPotion::AARBasePowerup_HealthPotion()
{
    CreditCost = 50;
}

void AARBasePowerup_HealthPotion::Interact_Implementation(APawn *InstigatorPawn)
{
    if (!InstigatorPawn) return;

    const auto AttributeComponent = UARAttributeComponent::GetAttributes(InstigatorPawn);

    if (AttributeComponent && !AttributeComponent->IsHealthFull())
    {
        if(const auto PS = InstigatorPawn->GetPlayerState<AARPlayerState>())
        {
            if (PS->RemoveCredits(CreditCost) && AttributeComponent->ApplyHealthChange(this, AttributeComponent->GetMaxHealth()))
            {
                HideAndCooldownPowerup();
            }
        }
    }
}
