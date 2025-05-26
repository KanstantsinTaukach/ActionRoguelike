// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "Components/ARAttributeComponent.h"
#include "../ARGameModeBase.h"

UARAttributeComponent::UARAttributeComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    Health = MaxHealth;
}

bool UARAttributeComponent::ApplyHealthChange(AActor *InstigatorActor, float Delta)
{
    if (!GetOwner()->CanBeDamaged())
    {
        return false;
    }

    float OldHealth = Health;
    Health = FMath::Clamp(Health + Delta, 0.0f, MaxHealth);

    float ActualDelta = Health - OldHealth;

    OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDelta);

    if (ActualDelta < 0.0f && Health == 0.0f)
    {
        const auto GameMode = GetWorld()->GetAuthGameMode<AARGameModeBase>();
        if (GameMode)
        {
            GameMode->OnActorKilled(GetOwner(), InstigatorActor);
        }
    }
    return ActualDelta != 0.0f;
}

UARAttributeComponent *UARAttributeComponent::GetAttributes(AActor *FromActor)
{
    if (FromActor)
    {
        return Cast<UARAttributeComponent>(FromActor->GetComponentByClass(UARAttributeComponent::StaticClass()));
    }

    return nullptr;
}

bool UARAttributeComponent::IsActorAlive(AActor *Actor)
{
    if (!Actor) return false;

    UARAttributeComponent *AttributeComp = GetAttributes(Actor);
    if (AttributeComp)
    {
        return AttributeComp->IsAlive();
    }

    return false;
}

bool UARAttributeComponent::Kill(AActor *InstigatorActor)
{
    return ApplyHealthChange(InstigatorActor, -GetMaxHealth());
}