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

    // Leaving this on applies small constant force via component 'tick' (Optional)
	RadialForceComp->SetAutoActivate(false);

	RadialForceComp->Radius = 750.0f;
    RadialForceComp->ImpulseStrength = 2500.0f; // Alternative: 200000.0f if bImpulseVelChange = false
    // Optional, ignores 'Mass' of other objects (if false, the impulse strength will be much higher to push most objects depending on Mass)
    RadialForceComp->bImpulseVelChange = true;

    // Optional, default constructor of component already adds 4 object types to affect, excluding WorldDynamic
	RadialForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);

    // Binding either in constructor or in BeginPlay() or in PostInitializeComponents() below
    // StaticMeshComp->OnComponentHit.AddDynamic(this, &AARExplosiveBarrel::OnActorHit);
}

void AARExplosiveBarrel::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    StaticMeshComp->OnComponentHit.AddDynamic(this, &AARExplosiveBarrel::OnActorHit);
}

void AARExplosiveBarrel::OnActorHit(UPrimitiveComponent *HitComponent, AActor *OtherActor,
                                    UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
    RadialForceComp->FireImpulse();
}

void AARExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();	
}
