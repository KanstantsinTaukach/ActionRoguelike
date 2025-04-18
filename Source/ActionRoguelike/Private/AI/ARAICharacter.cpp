// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "AI/ARAICharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/ARAttributeComponent.h"

AARAICharacter::AARAICharacter()
{
    PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

    AttributeComp = CreateDefaultSubobject<UARAttributeComponent>("AttributeComp");

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AARAICharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    PawnSensingComp->OnSeePawn.AddDynamic(this, &AARAICharacter::OnPawnSeen);
}

void AARAICharacter::OnPawnSeen(APawn *Pawn)
{
    const auto AIController = Cast<AAIController>(GetController());
    if (AIController)
    {
        const auto BlackboardComponent = AIController->GetBlackboardComponent();

        BlackboardComponent->SetValueAsObject("TargetActor", Pawn);

        DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.0f, true);
    }
}