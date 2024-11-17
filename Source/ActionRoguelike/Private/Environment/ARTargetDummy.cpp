// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "Environment/ARTargetDummy.h"
#include "Components/StaticMeshComponent.h"
#include "ARAttributeComponent.h"

AARTargetDummy::AARTargetDummy()
{
    PrimaryActorTick.bCanEverTick = false;

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
    RootComponent = MeshComp;

    AttributeComp = CreateDefaultSubobject<UARAttributeComponent>("AttributeComp");
    // Trigger when health is changed (damage/healing)
    AttributeComp->OnHealthChanged.AddDynamic(this, &AARTargetDummy::OnHealthChanged);
}

void AARTargetDummy::OnHealthChanged(AActor *InstigatorActor, UARAttributeComponent *OwningComp, float NewHealth,
                                     float Delta)
{
    if (Delta < 0.0f)
    {
        MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
    }
}
