// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.


#include "Components/ARActionComponent.h"
#include "Actions/ARAction.h"

UARActionComponent::UARActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UARActionComponent::BeginPlay()
{
	Super::BeginPlay();

    for (TSubclassOf<UARAction> ActionClass : DefaultActions)
    {
        AddAction(ActionClass);
    }
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
            if (!Action->CanStart(Instigator))
            {
                FString FailedMsg = FString::Printf(TEXT("Failed to run: %s"), *ActionName.ToString());
                GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FailedMsg);

                continue;
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
