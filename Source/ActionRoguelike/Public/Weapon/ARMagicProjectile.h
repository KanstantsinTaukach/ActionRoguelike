// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ARProjectileBase.h"
#include "ARMagicProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AARMagicProjectile : public AARProjectileBase // Re-parented form Actor
{
    GENERATED_BODY()

  public:
    AARMagicProjectile();
    
  protected:
    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    float DamageAmount;

    UFUNCTION()
    void OnActorOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                        int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

};
