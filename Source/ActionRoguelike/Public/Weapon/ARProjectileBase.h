// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARProjectileBase.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UAudioComponent;
class USoundCue;

UCLASS(ABSTRACT) // "ABSTRACT" marks this class as incomplete, keeping this out of certain dropdowns windows like SpawnActor in Unreal Editor
class ACTIONROGUELIKE_API AARProjectileBase : public AActor
{
    GENERATED_BODY()

  public:
    AARProjectileBase();

  protected:
    UPROPERTY(EditDefaultsOnly, Category = "Effects")
    UParticleSystem *ImpactVFX;
    UPROPERTY(EditDefaultsOnly, Category = "Sounds")
    USoundCue *ImpactSound;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USphereComponent *SphereComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UProjectileMovementComponent *MovementComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UParticleSystemComponent *EffectComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UAudioComponent *AudioComp;

    UFUNCTION()
    virtual void OnActorHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                            FVector NormalImpulse, const FHitResult &Hit);

    // BlueprintNativeEvent = C++ base implementation, can be expanded in Blueprints
    // BlueprintCallable to allow child classes to trigger explosions
    // Nor required for assignment, useful for expanging in Blueprint later on

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Explode();

    virtual void PostInitializeComponents() override;
};
