// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "ARAttributeComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API UARAttributeComponent : public UActorComponent
{
    GENERATED_BODY()

  public:
    UARAttributeComponent();

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
    float Health;

  public:
    UFUNCTION(BlueprintCallable, Category = "Attributes")
    bool ApplyHealthChange(float Delta);
};
