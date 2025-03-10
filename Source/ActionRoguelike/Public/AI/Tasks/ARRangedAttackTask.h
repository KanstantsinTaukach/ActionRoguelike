// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "CoreMinimal.h"
#include "ARRangedAttackTask.generated.h"

UCLASS()
class ACTIONROGUELIKE_API UARRangedAttackTask : public UBTTaskNode
{
    GENERATED_BODY()

  private:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;

  protected:
    UPROPERTY(EditAnywhere, Category = "AI")
    TSubclassOf<AActor> ProjectileClass;
};
