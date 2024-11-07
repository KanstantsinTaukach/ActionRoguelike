// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/ARGameplayInterface.h"
#include "ARItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API AARItemChest : public AActor, public IARGameplayInterface
{
    GENERATED_BODY()

  public:
    UPROPERTY(EditAnywhere)
    float TargetPitch;

    void Interact_Implementation(APawn *InstigatorPawn);

    AARItemChest();

  protected:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent *BaseMesh;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent *LidMesh;

    virtual void BeginPlay() override;

  public:
    virtual void Tick(float DeltaTime) override;
};
