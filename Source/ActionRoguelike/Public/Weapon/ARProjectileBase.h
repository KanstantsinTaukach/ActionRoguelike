// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARProjectileBase.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS(ABSTRACT)
class ACTIONROGUELIKE_API AARProjectileBase : public AActor
{
    GENERATED_BODY()

  public:
    AARProjectileBase();

  protected:
    UPROPERTY(EditDefaultsOnly, Category = "Effects")
    UParticleSystem *ImpactVFX;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects")
    USphereComponent *SphereComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects")
    UProjectileMovementComponent *MovementComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects")
    UParticleSystemComponent *EffectComp;

    UFUNCTION()
    virtual void OnActorHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                            FVector NormalImpulse, const FHitResult &Hit);

    // BlueprintNativeEvent = C++ base implementation, can be expanded in Blueprints
    // BlueprintCallable to allow child classes to trigger explosions

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Explode();

    virtual void PostInitializeComponents() override;
};
