// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PowerUps/ARBasePowerup.h"
#include "ARBasePowerup_Credits.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AARBasePowerup_Credits : public AARBasePowerup
{
    GENERATED_BODY()

public:
    AARBasePowerup_Credits();

    void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
    UPROPERTY(EditAnywhere, Category = "Credits")
    int32 CreditsAmount;
};
