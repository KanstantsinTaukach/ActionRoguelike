// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.


#include "Actions/ARAction.h"

DEFINE_LOG_CATEGORY_STATIC(ARAction, All, All);

void UARAction::StartAction_Implementation(AActor *Instigator)
{
    UE_LOG(ARAction, Log, TEXT("Start action: %s"), *GetNameSafe(this));
}

void UARAction::StopAction_Implementation(AActor *Instigator)
{
    UE_LOG(ARAction, Log, TEXT("Stop action: %s"), *GetNameSafe(this));
}

UWorld* UARAction::GetWorld() const
{
    // Outer is set when creating action via NewObject<T>
    UActorComponent* const Comp = Cast<UActorComponent>(GetOuter());
    if (Comp)
    {
        return Comp->GetWorld();
    }

    return nullptr;
}
