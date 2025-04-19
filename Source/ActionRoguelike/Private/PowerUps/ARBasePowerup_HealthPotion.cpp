// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "PowerUps/ARBasePowerup_HealthPotion.h"
#include "ARAttributeComponent.h"

AARBasePowerup_HealthPotion::AARBasePowerup_HealthPotion()
{
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    MeshComponent->SetupAttachment(RootComponent);
}

void AARBasePowerup_HealthPotion::Interact_Implementation(APawn *InstigatorPawn)
{
    if (!InstigatorPawn) return;

    const auto AttributeComponent = Cast<UARAttributeComponent>(InstigatorPawn->GetComponentByClass(UARAttributeComponent::StaticClass()));

    if (AttributeComponent && !AttributeComponent->IsHealthFull())
    {
        if (AttributeComponent->ApplyHealthChange(this, AttributeComponent->GetMaxHealth()))
        {
            HideAndCooldownPowerup();
        }
    }
}
