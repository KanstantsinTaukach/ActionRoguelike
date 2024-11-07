// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "Environment/ARExplosiveBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

AARExplosiveBarrel::AARExplosiveBarrel()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
    StaticMeshComp->SetSimulatePhysics(true);
    RootComponent = StaticMeshComp;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
    RadialForceComp->SetupAttachment(StaticMeshComp);
}

void AARExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();	
}
