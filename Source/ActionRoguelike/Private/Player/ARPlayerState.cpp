// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "Player/ARPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(ARPlayerStateLog, All, All);

void AARPlayerState::AddCredits(int32 Delta)
{
    if (!ensure(Delta > 0))
    {
        return;
    }

    Credits += Delta;

    OnCreditsChanged.Broadcast(this, Credits, Delta);

    UE_LOG(ARPlayerStateLog, Warning, TEXT("Add credits"));
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

    UE_LOG(ARPlayerStateLog, Warning, TEXT("Remove credits"));

    return true;
}
