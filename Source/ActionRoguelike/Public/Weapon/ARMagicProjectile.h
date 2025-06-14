// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ARProjectileBase.h"
#include "GameplayTagContainer.h"
#include "ARMagicProjectile.generated.h"

class UARAction_Effect;

UCLASS()
class ACTIONROGUELIKE_API AARMagicProjectile : public AARProjectileBase 
{
    GENERATED_BODY()

  public:
    AARMagicProjectile();
    
  protected:
    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    float DamageAmount;

    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    FGameplayTag ParryTag;

    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    TSubclassOf<UARAction_Effect> BurningActionClass;

    UFUNCTION()
    void OnActorOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                        int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

};
