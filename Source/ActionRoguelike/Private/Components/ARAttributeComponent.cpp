// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "Components/ARAttributeComponent.h"

UARAttributeComponent::UARAttributeComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    Health = MaxHealth;
}

bool UARAttributeComponent::ApplyHealthChange(float Delta)
{
    float OldHealth = Health;
    Health = FMath::Clamp(Health + Delta, 0.0f, MaxHealth);

    float ActualDelta = Health - OldHealth;

    OnHealthChanged.Broadcast(nullptr, this, Health, ActualDelta);

    return ActualDelta != 0.0f;
}