// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ARGameplayInterface.generated.h"

UINTERFACE(MinimalAPI)
class UARGameplayInterface : public UInterface
{
    GENERATED_BODY()
};

class ACTIONROGUELIKE_API IARGameplayInterface
{
    GENERATED_BODY()

  public:
    UFUNCTION(BlueprintNativeEvent)
    void Interact(APawn *InstigatorPawn);
};
