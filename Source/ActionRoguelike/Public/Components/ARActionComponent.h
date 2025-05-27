// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "ARActionComponent.generated.h"

class UARAction;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API UARActionComponent : public UActorComponent
{
    GENERATED_BODY()

  public:
    UARActionComponent();

    UFUNCTION(BlueprintCallable, Category = "Actions")
    void AddAction(TSubclassOf<UARAction> ActionClass);

    UFUNCTION(BlueprintCallable, Category = "Actions")
    bool StartActionByName(AActor *Instigator, FName ActionName);

    UFUNCTION(BlueprintCallable, Category = "Actions")
    bool StopActionByName(AActor *Instigator, FName ActionName);

  protected:
    UPROPERTY()
    TArray<UARAction *> Actions;

    virtual void BeginPlay() override;
};
