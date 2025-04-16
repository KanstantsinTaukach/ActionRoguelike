// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "ARGameplayInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARBasePowerup.generated.h"

class USphereComponent;

UCLASS()
class ACTIONROGUELIKE_API AARBasePowerup : public AActor, public IARGameplayInterface
{
    GENERATED_BODY()

  public:
    AARBasePowerup();

    void Interact_Implementation(APawn *InstigatorPawn);

  protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    USphereComponent *CollisionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powerup")
    float RespawnTime = 10.0f;

    UFUNCTION()
    void ShowPowerup();

    void HideAndCooldownPowerup();

    void SetPowerupState(bool bNewIsActive);

  private:
    FTimerHandle RespawnTimerHandle;
};
