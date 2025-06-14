// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "ARAction.generated.h"

class UWorld;
class UARActionComponent;

UCLASS(Blueprintable)
class ACTIONROGUELIKE_API UARAction : public UObject
{
    GENERATED_BODY()

protected:
    // Tags added to owning actor when activated, removed when action stops
    UPROPERTY(EditDefaultsOnly, Category = "Tags")
    FGameplayTagContainer GrantsTags;

    // Action can only start if OwningActor has none of these Tags applied
    UPROPERTY(EditDefaultsOnly, Category = "Tags")
    FGameplayTagContainer BlockedTags;

    UFUNCTION(BlueprintCallable, Category = "Action")
    UARActionComponent* GetOwningComponent() const;

    bool bIsRunning;

public:
    // Start immediately when added to an action component
    UPROPERTY(EditDefaultsOnly, Category = "Action")
    bool bAutoStart;

    UPROPERTY(EditDefaultsOnly, Category = "Action")
    FName ActionName;

    UFUNCTION(BlueprintNativeEvent, Category = "Action")
    bool CanStart(AActor* Instigator);

    UFUNCTION(BlueprintNativeEvent, Category = "Action")
    void StartAction(AActor* Instigator);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Action")
    void StopAction(AActor* Instigator);

    UFUNCTION(BlueprintCallable, Category = "Action")
    bool GetIsRunning() const { return bIsRunning; };

    UWorld* GetWorld() const override;
};
