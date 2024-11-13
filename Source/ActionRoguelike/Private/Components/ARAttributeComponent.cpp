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

    return true;
}