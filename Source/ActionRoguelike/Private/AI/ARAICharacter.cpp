// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "AI/ARAICharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/ARAttributeComponent.h"
#include "BrainComponent.h"
#include "UI/ARWorldUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AARAICharacter::AARAICharacter()
{
    PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

    AttributeComp = CreateDefaultSubobject<UARAttributeComponent>("AttributeComp");

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
    GetMesh()->SetGenerateOverlapEvents(true);

    TimeToHitParamName = "TimeToHit";
}

void AARAICharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    PawnSensingComp->OnSeePawn.AddDynamic(this, &AARAICharacter::OnPawnSeen);

    AttributeComp->OnHealthChanged.AddDynamic(this, &AARAICharacter::OnHealthChanged);
}


void AARAICharacter::OnPawnSeen(APawn *Pawn)
{
    SetTargetActor(Pawn);
}

void AARAICharacter::SetTargetActor(AActor *NewTarget)
{
    const auto AIController = Cast<AAIController>(GetController());
    if (AIController)
    {
        AIController->GetBlackboardComponent()->SetValueAsObject("TargetActor", NewTarget);
    }
}

void AARAICharacter::OnHealthChanged(AActor *InstigatorActor, UARAttributeComponent *OwningComp, float NewHealth, float Delta)
{
    if (Delta < 0.0f)
    {
        if (InstigatorActor != this)
        {
            SetTargetActor(InstigatorActor);
        }

        if (ActiveHealthBar == nullptr)
        {
            ActiveHealthBar = CreateWidget<UARWorldUserWidget>(GetWorld(), HealthBarWidgetClass);
            if (ActiveHealthBar)
            {
                ActiveHealthBar->AttachedActor = this;
                ActiveHealthBar->AddToViewport();
            }
        }

        GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->TimeSeconds);

        if (NewHealth <= 0.0f)
        {
            // stop BT
            const auto AIController = Cast<AAIController>(GetController());
            if (AIController)
            {
                AIController->GetBrainComponent()->StopLogic("Killed");
            }

            // ragdoll
            GetMesh()->SetAllBodiesSimulatePhysics(true);
            GetMesh()->SetCollisionProfileName("Ragdoll");

            GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            GetCharacterMovement()->DisableMovement();

            SetLifeSpan(10.0f);
        }
    }    
}