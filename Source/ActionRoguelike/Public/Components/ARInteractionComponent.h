// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "ARInteractionComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API UARInteractionComponent : public UActorComponent
{
    GENERATED_BODY()

  public:
    UARInteractionComponent();

    void PrimaryInteract();
};
