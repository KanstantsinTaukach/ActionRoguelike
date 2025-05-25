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

    UFUNCTION(BlueprintCallable, Category = "Attributes")
    static UARAttributeComponent *GetAttributes(AActor *FromActor);

    UFUNCTION(BlueprintCallable, Category = "Attributes", meta = (DisplayName = "IsAlive"))
    static bool IsActorAlive(AActor *Actor);

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
    float Health;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
    float MaxHealth = 100.0f;

  public:
    UPROPERTY(BlueprintAssignable)
    FOnHealthChangedSignature OnHealthChanged;

    UFUNCTION(BlueprintCallable, Category = "Attributes")
    bool ApplyHealthChange(AActor *InstigatorActor, float Delta);

    UFUNCTION(BlueprintCallable)
    bool IsAlive() const { return Health > 0.0f; };

    UFUNCTION(BlueprintCallable)
    bool IsHealthFull() const { return Health == MaxHealth; };

    UFUNCTION(BlueprintCallable)
    float GetHealth() const { return Health; };

    UFUNCTION(BlueprintCallable)
    float GetMaxHealth() const { return MaxHealth; };

    UFUNCTION(BlueprintCallable)
    bool Kill(AActor *InstigatorActor);
};
