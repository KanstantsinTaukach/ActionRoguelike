// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.


#include "Components/ARActionComponent.h"
#include "Player/ARAction.h"

UARActionComponent::UARActionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UARActionComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void UARActionComponent::AddAction(TSubclassOf<UARAction> ActionClass)
{
    if (!ensure(ActionClass)) { return; }

    const auto NewAction = NewObject<UARAction>(this, ActionClass);
    if (ensure(NewAction))
    {
        Actions.Add(NewAction);
    }
}

bool UARActionComponent::StartActionByName(AActor *Instigator, FName ActionName)
{
    for (const auto Action : Actions)
    {
        if (Action && Action->ActionName == ActionName)
        {
            Action->StartAction(Instigator);
            return true;
        }
    }

    return false;
}

bool UARActionComponent::StopActionByName(AActor *Instigator, FName ActionName)
{
    for (const auto Action : Actions)
    {
        if (Action && Action->ActionName == ActionName)
        {
            Action->StopAction(Instigator);
            return true;
        }
    }

    return false;
}