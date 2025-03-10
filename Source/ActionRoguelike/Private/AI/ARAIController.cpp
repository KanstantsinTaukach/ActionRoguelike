// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "AI/ARAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AARAIController::BeginPlay()
{
    Super::BeginPlay();

    RunBehaviorTree(BehaviorTree);

   APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
   if (MyPawn)
   {
       GetBlackboardComponent()->SetValueAsVector("MoveToLocation", MyPawn->GetActorLocation());

       GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);
   }
}
