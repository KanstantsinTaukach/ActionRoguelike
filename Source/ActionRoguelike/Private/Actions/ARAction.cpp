// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.


#include "Actions/ARAction.h"
#include "Components/ARActionComponent.h"

DEFINE_LOG_CATEGORY_STATIC(ARAction, All, All);

bool UARAction::CanStart_Implementation(AActor* Instigator)
{
    if (GetIsRunning()) { return false; }

    const auto Comp = GetOwningComponent();
    if (Comp->ActiveGameplayTags.HasAny(BlockedTags))
    {
        return false;
    }

    return true;
}

void UARAction::StartAction_Implementation(AActor *Instigator)
{
    UE_LOG(ARAction, Log, TEXT("Start action: %s"), *GetNameSafe(this));

    const auto Comp = GetOwningComponent();
    Comp->ActiveGameplayTags.AppendTags(GrantsTags);

    bIsRunning = true;
}

void UARAction::StopAction_Implementation(AActor *Instigator)
{
    UE_LOG(ARAction, Log, TEXT("Stop action: %s"), *GetNameSafe(this));

    ensureAlways(bIsRunning);

    const auto Comp = GetOwningComponent();
    Comp->ActiveGameplayTags.RemoveTags(GrantsTags);

    bIsRunning = false;
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

UARActionComponent* UARAction::GetOwningComponent() const
{
    return Cast<UARActionComponent>(GetOuter());
}