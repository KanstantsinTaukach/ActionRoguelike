// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARExplosiveBarrel.generated.h"

class UStaticMeshComponent;
class URadialForceComponent;

UCLASS()
class ACTIONROGUELIKE_API AARExplosiveBarrel : public AActor
{
    GENERATED_BODY()

  public:
    AARExplosiveBarrel();

  protected:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent *StaticMeshComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    URadialForceComponent *RadialForceComp;

    virtual void PostInitializeComponents() override;

    UFUNCTION()
    void OnActorHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
                    FVector NormalImpulse, const FHitResult &Hit);

    virtual void BeginPlay() override;
};
