// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "Player/ARCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/ARInteractionComponent.h"
#include "Components/ARAttributeComponent.h"
#include "Components/ARActionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(ARCharacterLog, All, All);

AARCharacter::AARCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
    SpringArmComp->bUsePawnControlRotation = true;
    SpringArmComp->SetupAttachment(RootComponent);

    CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
    CameraComp->SetupAttachment(SpringArmComp);

    InteractionComp = CreateDefaultSubobject<UARInteractionComponent>("InteractionComp");

    AttributeComp = CreateDefaultSubobject<UARAttributeComponent>("AttributeComp");

    ActionComp = CreateDefaultSubobject<UARActionComponent>("ActionComp");

    GetCharacterMovement()->bOrientRotationToMovement = true;

    bUseControllerRotationYaw = false;

    TimeToHitParamName = "TimeToHit";
}

void AARCharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    AttributeComp->OnHealthChanged.AddDynamic(this, &AARCharacter::OnHealthChanged);
}

FVector AARCharacter::GetPawnViewLocation() const
{
    return CameraComp->GetComponentLocation();
}

void AARCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AARCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AARCharacter::MoveRight);

    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

    PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AARCharacter::PrimaryAttack);
    PlayerInputComponent->BindAction("SecondaryAttack", IE_Pressed, this, &AARCharacter::BlackHoleAttack);
    PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AARCharacter::Dash);

    PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AARCharacter::PrimaryInteract);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AARCharacter::SprintStart);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AARCharacter::SprintStop);
}

void AARCharacter::MoveForward(float Value)
{
    FRotator ControlRot = GetControlRotation();
    ControlRot.Pitch = 0.0f;
    ControlRot.Roll = 0.0f;

    AddMovementInput(ControlRot.Vector(), Value);
}

void AARCharacter::MoveRight(float Value)
{
    FRotator ControlRot = GetControlRotation();
    ControlRot.Pitch = 0.0f;
    ControlRot.Roll = 0.0f;

    FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

    AddMovementInput(RightVector, Value);
}

void AARCharacter::SprintStart()
{
    ActionComp->StartActionByName(this, "Sprint");
}

void AARCharacter::SprintStop()
{
    ActionComp->StopActionByName(this, "Sprint");
}

void AARCharacter::PrimaryAttack()
{
    ActionComp->StartActionByName(this, "PrimaryAttack");
}

void AARCharacter::BlackHoleAttack()
{
    ActionComp->StartActionByName(this, "SecondaryAttack");
}

void AARCharacter::Dash()
{
    ActionComp->StartActionByName(this, "Dash");
}

void AARCharacter::PrimaryInteract()
{
    if (InteractionComp)
    {
        InteractionComp->PrimaryInteract();
    }
}

void AARCharacter::OnHealthChanged(AActor *InstigatorActor, UARAttributeComponent *OwningComp, float NewHealth, float Delta)
{
    if (Delta < 0.0f)
    {
        GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->TimeSeconds);
    }

    if (NewHealth <= 0.0f && Delta < 0.0f)
    {
        APlayerController* PC = Cast<APlayerController>(GetController());
        DisableInput(PC);
    }
}

void AARCharacter::HealSelf(float Amount /* = 100.0f */)
{
    AttributeComp->ApplyHealthChange(this, Amount);
}