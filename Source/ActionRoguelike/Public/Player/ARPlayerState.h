// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ARPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChangedSignature, AARPlayerState*, PlayerState, int32, NewCredits, int32, Delta);

UCLASS()
class ACTIONROGUELIKE_API AARPlayerState : public APlayerState
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Credits")
    int32 Credits;

public:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnCreditsChangedSignature OnCreditsChanged;

    UFUNCTION(BlueprintCallable, Category = "Credits")
    int32 GetCredits() const { return Credits; };

    UFUNCTION(BlueprintCallable, Category = "Credits")
    void AddCredits(int32 Delta);

    UFUNCTION(BlueprintCallable, Category = "Credits")
    bool RemoveCredits(int32 Delta);
};
