// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ARAction.generated.h"

class UWorld;

UCLASS(Blueprintable)
class ACTIONROGUELIKE_API UARAction : public UObject
{
    GENERATED_BODY()

  public:
    UPROPERTY(EditDefaultsOnly, Category = "Action")
    FName ActionName;

    UFUNCTION(BlueprintNativeEvent, Category = "Action")
    void StartAction(AActor *Instigator);

    UFUNCTION(BlueprintNativeEvent, Category = "Action")
    void StopAction(AActor *Instigator);

    UWorld* GetWorld() const override;
};
