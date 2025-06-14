// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PowerUps/ARBasePowerup.h"
#include "ARBasePowerup_HealthPotion.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AARBasePowerup_HealthPotion : public AARBasePowerup
{
    GENERATED_BODY()

public:
    AARBasePowerup_HealthPotion();

    void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
    UPROPERTY(EditAnywhere, Category = "HealthPotion")
    int32 CreditsCost;
};
