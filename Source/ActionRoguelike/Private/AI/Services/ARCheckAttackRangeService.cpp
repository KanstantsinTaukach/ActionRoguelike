// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "AI/Services/ARCheckAttackRangeService.h"
#include "BehaviorTree//BlackboardComponent.h"
#include "AIController.h"

void UARCheckAttackRangeService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    // Check distance between AI and target actor

    const auto BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (ensure(BlackboardComp))
    {
        const auto TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject("TargetActor"));
        if (TargetActor)
        {
            const auto MyController = OwnerComp.GetAIOwner();
            const auto AIPawn = MyController->GetPawn();
            if(ensure(MyController) && ensure(AIPawn))
            {
                float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

                bool bWithinRange = DistanceTo < 2000.0f;

                bool bHasLOS = false;
                if (bWithinRange)
                {
                    bHasLOS = MyController->LineOfSightTo(TargetActor);
                }

                BlackboardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, (bWithinRange && bHasLOS));
            }
        }
    }
}
