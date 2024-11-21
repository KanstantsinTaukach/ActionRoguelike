// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "Player/ARCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/ARInteractionComponent.h"
#include "Components/ARAttributeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY_STATIC(CharacterLog, All, All);

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

    GetCharacterMovement()->bOrientRotationToMovement = true;

    bUseControllerRotationYaw = false;

    AttackAnimDelay = 0.2f;
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

    GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AARCharacter::PrimaryAttack_TimeElapsed, AttackAnimDelay);
}

void AARCharacter::PrimaryAttack_TimeElapsed()
{    
    SpawnProjectile(ProjectileClass);
}

void AARCharacter::BlackHoleAttack()
{
    PlayAnimMontage(AttackAnim);

    GetWorldTimerManager().SetTimer(TimerHandle_BlackHoleAttack, this, &AARCharacter::BlackHoleAttack_TimeElapsed, AttackAnimDelay);
}

void AARCharacter::BlackHoleAttack_TimeElapsed()
{
    SpawnProjectile(BlackHoleProjectileClass);
}

void AARCharacter::Dash()
{
    PlayAnimMontage(AttackAnim);

    GetWorldTimerManager().SetTimer(TimerHandle_DashAttack, this, &AARCharacter::Dash_TimeElapsed, AttackAnimDelay);
}

void AARCharacter::Dash_TimeElapsed()
{
    SpawnProjectile(DashProjectileClass);
}

void AARCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
    if (ensure(ClassToSpawn))
    {
        const FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        SpawnParams.Instigator = this;

        FCollisionShape Shape;
        Shape.SetSphere(20.0f);

        //Ignore Player
        FCollisionQueryParams Params;
        Params.AddIgnoredActor(this);

        FCollisionObjectQueryParams ObjParams;
        ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
        ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
        ObjParams.AddObjectTypesToQuery(ECC_Pawn);

        FVector TraceStart = CameraComp->GetComponentLocation();

        // Endpoint far into the look-at distance (not too far, still adjuxt somewhat towards crosshair on a miss)
        FVector TraceEnd = CameraComp->GetComponentLocation() + (GetControlRotation().Vector() * 5000.0f);

        FHitResult Hit;
        // Returns true if we got to a blocking hit
        if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params))
        {
            TraceEnd = Hit.ImpactPoint;
        }

        // Find new direction/rotation from Hand pointing to impact point in world.
        FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();

        FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
        GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTM, SpawnParams);
    }
}

void AARCharacter::PrimaryInteract()
{
    if (InteractionComp)
    {
        InteractionComp->PrimaryInteract();
    }
}
