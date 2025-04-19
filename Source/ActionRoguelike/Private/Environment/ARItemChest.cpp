// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "Environment/ARItemChest.h"
#include "Components/StaticMeshComponent.h"

AARItemChest::AARItemChest()
{
    PrimaryActorTick.bCanEverTick = true;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
    RootComponent = BaseMesh;

    LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
    LidMesh->SetupAttachment(BaseMesh);

    TargetPitch = 110.0f;
}

void AARItemChest::Interact_Implementation(APawn *InstigatorPawn)
{
    LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0.0f, 0.0f));
}