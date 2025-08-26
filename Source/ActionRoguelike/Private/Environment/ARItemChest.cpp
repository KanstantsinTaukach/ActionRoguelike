// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "Environment/ARItemChest.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"

AARItemChest::AARItemChest()
{
    PrimaryActorTick.bCanEverTick = true;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
    RootComponent = BaseMesh;

    LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
    LidMesh->SetupAttachment(BaseMesh);

    TargetPitch = 110.0f;

    SetReplicates(true);
}

void AARItemChest::Interact_Implementation(APawn *InstigatorPawn)
{
    bLidOpened = !bLidOpened;

    OnRep_LidOpened();
}

void AARItemChest::OnRep_LidOpened() 
{
    float CurrentPitch = bLidOpened ? TargetPitch : 0.0f;
    LidMesh->SetRelativeRotation(FRotator(CurrentPitch, 0.0f, 0.0f));
}

void AARItemChest::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AARItemChest, bLidOpened);
}