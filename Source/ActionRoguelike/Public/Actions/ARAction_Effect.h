// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ARAction.h"
#include "ARAction_Effect.generated.h"

UCLASS()
class ACTIONROGUELIKE_API UARAction_Effect : public UARAction
{
    GENERATED_BODY()

public:
    UARAction_Effect();

    void StartAction_Implementation(AActor* Instigator) override;

    void StopAction_Implementation(AActor* Instigator) override;

protected:
    FTimerHandle DurationTimerHandle;
    FTimerHandle PeriodTimerHandle;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
    float Duration;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
    float Period;

    UFUNCTION(BlueprintNativeEvent, Category = "Effect")
    void ExecutePeriodiceEffect(AActor* Instigator);
};
