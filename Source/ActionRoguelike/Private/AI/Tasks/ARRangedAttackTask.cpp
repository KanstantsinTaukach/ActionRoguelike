// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "AI/Tasks/ARRangedAttackTask.h"
#include "AIController.h"
#include "BehaviorTree//BlackboardComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type UARRangedAttackTask::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    const auto MyController = OwnerComp.GetAIOwner();
    if (ensure(MyController))
    {
        const auto MyPawn = Cast<ACharacter>(MyController->GetPawn());
        if (!MyPawn)
        {
            return EBTNodeResult::Failed;
        }

        FVector MuzzleLocation = MyPawn->GetMesh()->GetSocketLocation("Muzzle_01");

        const auto TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
        if (!TargetActor)
        {
            return EBTNodeResult::Failed;
        }

        FVector Direction = TargetActor->GetActorLocation() - MuzzleLocation;
        FRotator MuzzleRotation = Direction.Rotation();

        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        const auto NewProjectile =
            GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

        return NewProjectile ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
    }

    return EBTNodeResult::Failed;
}