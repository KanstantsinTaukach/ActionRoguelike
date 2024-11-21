// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "Components/ARAttributeComponent.h"

UARAttributeComponent::UARAttributeComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    Health = 100.0f;
}
bool UARAttributeComponent::ApplyHealthChange(float Delta)
{
    Health += Delta;

    OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

    return true;
}

bool UARAttributeComponent::IsAlive() const
{
    return Health > 0.0f;
}
