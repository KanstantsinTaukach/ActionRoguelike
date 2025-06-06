// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ARGameplayFunctionLibrary.generated.h"

UCLASS()
class ACTIONROGUELIKE_API UARGameplayFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

  public:
    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    static bool ApplyDamage(AActor *DamageCause, AActor *TargetActor, float DamageAmount);

    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    static bool ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount, const FHitResult& HitResult);
};
