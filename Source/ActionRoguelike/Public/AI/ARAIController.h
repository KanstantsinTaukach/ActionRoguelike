// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "AIController.h"
#include "CoreMinimal.h"
#include "ARAIController.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AARAIController : public AAIController
{
    GENERATED_BODY()

  protected:
    UPROPERTY(EditDefaultsOnly, Category = "AI")
    UBehaviorTree *BehaviorTree; 

    virtual void BeginPlay() override;
};
