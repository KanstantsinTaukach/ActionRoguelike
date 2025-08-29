// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.


#include "Components/ARActionComponent.h"
#include "Actions/ARAction.h"

UARActionComponent::UARActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

    SetIsReplicatedByDefault(true);
}

void UARActionComponent::BeginPlay()
{
	Super::BeginPlay();

    for (TSubclassOf<UARAction> ActionClass : DefaultActions)
    {
        AddAction(GetOwner(), ActionClass);
    }
}

void UARActionComponent::AddAction(AActor* Instigator, TSubclassOf<UARAction> ActionClass)
{
    if (!ensure(ActionClass)) { return; }

    const auto NewAction = NewObject<UARAction>(this, ActionClass);
    if (ensure(NewAction))
    {
        Actions.Add(NewAction);

        if(NewAction->bAutoStart && ensure(NewAction->CanStart(Instigator)))
        {
            NewAction->StartAction(Instigator);
        }
    }
}

void UARActionComponent::RemoveAction(UARAction* ActionToRemove) 
{
    if(!ensure(ActionToRemove && !ActionToRemove->GetIsRunning()))
    {
        return;
    }

    Actions.Remove(ActionToRemove);
}

bool UARActionComponent::StartActionByName(AActor *Instigator, FName ActionName)
{
    for (const auto Action : Actions)
    {
        if (Action && Action->ActionName == ActionName)
        {
            if (!Action->CanStart(Instigator))
            {
                FString FailedMsg = FString::Printf(TEXT("Failed to run: %s"), *ActionName.ToString());
                GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FailedMsg);

                continue;
            }

            // Is client?
            if (!GetOwner()->HasAuthority())
            {
                ServerStartAction(Instigator, ActionName);
            }

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
            if (Action->GetIsRunning())
            {
                Action->StopAction(Instigator);
                return true;
            }
        }
    }

    return false;
}

void UARActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFuncion) 
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFuncion);

    FString DebugMsg = GetNameSafe(GetOwner()) + " : " + ActiveGameplayTags.ToStringSimple();
    GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green, DebugMsg);
}

void UARActionComponent::ServerStartAction_Implementation(AActor* Instigator, FName ActionName) 
{
    StartActionByName(Instigator, ActionName);
}