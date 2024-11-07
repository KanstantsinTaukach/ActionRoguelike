// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "Environment/ARExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"

AARExplosiveBarrel::AARExplosiveBarrel()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
    StaticMeshComp->SetupAttachment(RootComponent);
    StaticMeshComp->SetSimulatePhysics(true);

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
    RadialForceComp->SetupAttachment(StaticMeshComp);
}

void AARExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();	
}
