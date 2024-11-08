// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "Player/ARCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/ARInteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AARCharacter::AARCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
    SpringArmComp->bUsePawnControlRotation = true;
    SpringArmComp->SetupAttachment(RootComponent);

    CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
    CameraComp->SetupAttachment(SpringArmComp);

    InteractionComp = CreateDefaultSubobject<UARInteractionComponent>("InteractionComp");

    GetCharacterMovement()->bOrientRotationToMovement = true;

    bUseControllerRotationYaw = false;
}

void AARCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AARCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AARCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AARCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AARCharacter::MoveRight);

    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

    PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AARCharacter::PrimaryAttack);
    PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AARCharacter::PrimaryInteract);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
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

void AARCharacter::PrimaryAttack()
{
    PlayAnimMontage(AttackAnim);

    GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AARCharacter::PrimaryAttack_TimeElapsed, 0.2f);

    // GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
}

void AARCharacter::PrimaryAttack_TimeElapsed()
{
    FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

    FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

void AARCharacter::PrimaryInteract()
{
    if (InteractionComp)
    {
        InteractionComp->PrimaryInteract();
    }
}
