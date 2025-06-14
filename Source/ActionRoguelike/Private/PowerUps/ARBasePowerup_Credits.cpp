// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "PowerUps/ARBasePowerup_Credits.h"
#include "Player/ARPlayerState.h"

AARBasePowerup_Credits::AARBasePowerup_Credits() 
{
    CreditsAmount = 70;
}

void AARBasePowerup_Credits::Interact_Implementation(APawn* InstigatorPawn) 
{
    if(!ensure(InstigatorPawn))
    {
        return;
    }

    if (AARPlayerState* PS = InstigatorPawn->GetPlayerState<AARPlayerState>())
    {
        PS->AddCredits(CreditsAmount);
        HideAndCooldownPowerup();
    }
}
