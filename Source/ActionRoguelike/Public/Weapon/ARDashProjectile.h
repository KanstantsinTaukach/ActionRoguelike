// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/ARProjectileBase.h"
#include "ARDashProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AARDashProjectile : public AARProjectileBase
{
    GENERATED_BODY()

  public:
    AARDashProjectile();

  protected:
    UPROPERTY(EditDefaultsOnly, Category = "Teleport")
    float TeleportDelay;

    UPROPERTY(EditDefaultsOnly, Category = "Teleport")
    float DetonateDelay;

    // Handle to cancel timer if we already hit something
    FTimerHandle TimerHandle_DelayedDetonate;

    // Base class using BlueprintNativeEvent, we must override the _Implementation not the Explode()
    virtual void Explode_Implementation() override;

    void TeleportInstigator();

    virtual void BeginPlay() override;
};
