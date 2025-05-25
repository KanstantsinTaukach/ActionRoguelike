// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "BehaviorTree/BTService.h"
#include "CoreMinimal.h"
#include "ARCheckLowHealthService.generated.h"

UCLASS()
class ACTIONROGUELIKE_API UARCheckLowHealthService : public UBTService
{
    GENERATED_BODY()

  protected:
    UPROPERTY(EditAnywhere, Category = "AI")
    FBlackboardKeySelector LowHealthKey;

    UPROPERTY(EditAnywhere, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float LowHealthFraction;

    virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;

  public:
    UARCheckLowHealthService();
};
