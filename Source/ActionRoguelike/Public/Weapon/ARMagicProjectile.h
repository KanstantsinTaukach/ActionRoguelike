// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class ACTIONROGUELIKE_API AARMagicProjectile : public AActor
{
    GENERATED_BODY()

  public:
    AARMagicProjectile();

  protected:
    UPROPERTY(VisibleAnywhere)
    USphereComponent *SphereComp;

    UPROPERTY(VisibleAnywhere)
    UProjectileMovementComponent *MovementComp;

    UPROPERTY(VisibleAnywhere)
    UParticleSystemComponent *EffectComp;

    virtual void BeginPlay() override;

  public:
    virtual void Tick(float DeltaTime) override;
};