// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "AI/Tasks/ARHealSelfTask.h"
#include "AIController.h"
#include "Components/ARAttributeComponent.h"

EBTNodeResult::Type UARHealSelfTask::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    const auto AIPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (!AIPawn) return EBTNodeResult::Failed;

    const auto AttributeComponent = UARAttributeComponent::GetAttributes(AIPawn);
    if (!AttributeComponent) return EBTNodeResult::Failed;

    AttributeComponent->ApplyHealthChange(AIPawn, AttributeComponent->GetMaxHealth());    
    
    return EBTNodeResult::Succeeded;
}
