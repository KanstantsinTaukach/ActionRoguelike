// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "ARCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AARCharacter::AARCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
    SpringArmComp->SetupAttachment(RootComponent);

    CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
    CameraComp->SetupAttachment(SpringArmComp);
}

void AARCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AARCharacter::MoveForward(float Value)
{
    AddMovementInput(GetActorForwardVector(), Value);
}

void AARCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AARCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AARCharacter::MoveForward);
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
}
