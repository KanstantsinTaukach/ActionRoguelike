// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "AI/Services/ARCheckLowHealthService.h"
#include "AIController.h"
#include "Components/ARAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UARCheckLowHealthService::UARCheckLowHealthService()
{
    NodeName = "Check Health";
    LowHealthFraction = 0.3f;
}

void UARCheckLowHealthService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    const auto AIPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (ensure(AIPawn))
    {
        const auto AttributeComponent = UARAttributeComponent::GetAttributes(AIPawn);
        if (ensure(AttributeComponent) && AttributeComponent->IsAlive())
        {
            bool bLowHealth = (AttributeComponent->GetHealth() / AttributeComponent->GetMaxHealth()) < LowHealthFraction;

            const auto BlackboardComponent = OwnerComp.GetBlackboardComponent();
            if (ensure(BlackboardComponent))
            {
                BlackboardComponent->SetValueAsBool(LowHealthKey.SelectedKeyName, bLowHealth);
            }
        }
    }
}