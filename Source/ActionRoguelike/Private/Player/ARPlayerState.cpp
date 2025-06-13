// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "Player/ARPlayerState.h"

void AARPlayerState::AddCredits(int32 Delta)
{
    if (ensure(Delta > 0))
    {
        return;
    }

    Credits += Delta;

    OnCreditsChanged.Broadcast(this, Credits, Delta);
}

bool AARPlayerState::RemoveCredits(int32 Delta)
{
    if (!ensure(Delta > 0))
    {
        return false;
    }

    if (Credits < Delta)
    {
        return false;
    }

    Credits -= Delta;

    OnCreditsChanged.Broadcast(this, Credits, Delta);

    return true;
}
