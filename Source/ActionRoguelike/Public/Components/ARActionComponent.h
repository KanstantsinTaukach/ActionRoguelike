// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ARActionComponent.generated.h"

class UARAction;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API UARActionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UARActionComponent();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
    FGameplayTagContainer ActiveGameplayTags;

    UFUNCTION(BlueprintCallable, Category = "Actions")
    void AddAction(AActor* Instigator, TSubclassOf<UARAction> ActionClass);

    UFUNCTION(BlueprintCallable, Category = "Actions")
    void RemoveAction(UARAction* ActionToRemove);

    UFUNCTION(BlueprintCallable, Category = "Actions")
    bool StartActionByName(AActor* Instigator, FName ActionName);

    UFUNCTION(BlueprintCallable, Category = "Actions")
    bool StopActionByName(AActor* Instigator, FName ActionName);

    void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFuncion) override;

protected:
    UPROPERTY(EditAnywhere, Category = "Actions")
    TArray<TSubclassOf<UARAction>> DefaultActions;

    UPROPERTY()
    TArray<UARAction*> Actions;

    virtual void BeginPlay() override;
};
