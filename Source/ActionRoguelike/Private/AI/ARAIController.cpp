// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "AI/ARAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AARAIController::BeginPlay()
{
    Super::BeginPlay();

    if (ensureMsgf(BehaviorTree, TEXT("Behavior Tree is nullptr! Please assign BehaviorTree in your AI Controller.")))
    {
        RunBehaviorTree(BehaviorTree);
    }
}
