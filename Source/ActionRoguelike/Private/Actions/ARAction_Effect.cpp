// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "Actions/ARAction_Effect.h"
#include "Components/ARActionComponent.h"

UARAction_Effect::UARAction_Effect() 
{
    bAutoStart = true;
}

void UARAction_Effect::StartAction_Implementation(AActor* Instigator)
{
    Super::StartAction_Implementation(Instigator);

    if (Duration > 0.0f)
    {
        FTimerDelegate Delegate;
        Delegate.BindUFunction(this, "StopAction", Instigator);
        GetWorld()->GetTimerManager().SetTimer(DurationTimerHandle, Delegate, Duration, false);
    }

    if (Period > 0.0f)
    {
        FTimerDelegate Delegate;
        Delegate.BindUFunction(this, "ExecutePeriodiceEffect", Instigator);
        GetWorld()->GetTimerManager().SetTimer(PeriodTimerHandle, Delegate, Period, true);
    }
}

void UARAction_Effect::StopAction_Implementation(AActor* Instigator)
{
    if(GetWorld()->GetTimerManager().GetTimerRemaining(PeriodTimerHandle) < KINDA_SMALL_NUMBER)
    {
        ExecutePeriodiceEffect(Instigator);
    }

    Super::StopAction_Implementation(Instigator);

    GetWorld()->GetTimerManager().ClearTimer(PeriodTimerHandle);
    GetWorld()->GetTimerManager().ClearTimer(DurationTimerHandle);

    const auto ActionComponent = GetOwningComponent();
    if(ActionComponent)
    {
        ActionComponent->RemoveAction(this);
    }
}

void UARAction_Effect::ExecutePeriodiceEffect_Implementation(AActor* Instigator) {}
