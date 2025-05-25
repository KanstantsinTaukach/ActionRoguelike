// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "CoreMinimal.h"
#include "ARHealSelfTask.generated.h"

UCLASS()
class ACTIONROGUELIKE_API UARHealSelfTask : public UBTTaskNode
{
    GENERATED_BODY()

  private:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
};
