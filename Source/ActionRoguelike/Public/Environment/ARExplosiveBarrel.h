// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARExplosiveBarrel.generated.h"

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

    virtual void BeginPlay() override;
};
