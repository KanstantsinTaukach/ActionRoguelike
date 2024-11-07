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

  protected:
    virtual void BeginPlay() override;

  public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction *ThisTickFunction) override;
};
