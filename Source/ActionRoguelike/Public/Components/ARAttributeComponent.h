// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "ARAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChangedSignature, AActor *, InstigatorActor,
                                              UARAttributeComponent *, OwningComp, float, NewHealth, float, Delta);

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
    UPROPERTY(BlueprintAssignable)
    FOnHealthChangedSignature OnHealthChanged;

    UFUNCTION(BlueprintCallable, Category = "Attributes")
    bool ApplyHealthChange(float Delta);

    UFUNCTION(BlueprintCallable)
    bool IsAlive() const;
};
