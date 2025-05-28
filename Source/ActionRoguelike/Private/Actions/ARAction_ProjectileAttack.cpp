// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "Actions/ARAction_ProjectileAttack.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

UARAction_ProjectileAttack::UARAction_ProjectileAttack()
{
    AttackAnimDelay = 0.2f;

    HandSocketName = "Muzzle_01";
}

void UARAction_ProjectileAttack::StartAction_Implementation(AActor* Instigator)
{
    Super::StartAction_Implementation(Instigator);

    const auto Character = Cast<ACharacter>(Instigator);
    if (Character)
    {
        Character->PlayAnimMontage(AttackAnim);

        if (CastingEffect)
        {
            UGameplayStatics::SpawnEmitterAttached(CastingEffect, Character->GetMesh(), HandSocketName, FVector::ZeroVector,
                FRotator::ZeroRotator, EAttachLocation::SnapToTarget);
        }

        FTimerHandle TimerHandle_AttackDelay;
        FTimerDelegate Delegate;
        Delegate.BindUFunction(this, "AttackDelay_Elapsed", Character);

        GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, AttackAnimDelay, false);
    }
}

void UARAction_ProjectileAttack::AttackDelay_Elapsed(ACharacter* InstigatorCharacter) 
{
    if (ensure(ProjectileClass))
    {
        const FVector HandLocation = InstigatorCharacter->GetMesh()->GetSocketLocation(HandSocketName);

        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        SpawnParams.Instigator = InstigatorCharacter;

        FCollisionShape Shape;
        Shape.SetSphere(20.0f);

        // Ignore Player
        FCollisionQueryParams Params;
        Params.AddIgnoredActor(InstigatorCharacter);

        FCollisionObjectQueryParams ObjParams;
        ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
        ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
        ObjParams.AddObjectTypesToQuery(ECC_Pawn);

        FVector TraceStart = InstigatorCharacter->GetPawnViewLocation();

        // Endpoint far into the look-at distance (not too far, still adjust somewhat towards crosshair on a miss)
        FVector TraceEnd = TraceStart + (InstigatorCharacter->GetControlRotation().Vector() * 5000.0f);

        FHitResult Hit;
        // Returns true if we got to a blocking hit
        if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params))
        {
            TraceEnd = Hit.ImpactPoint;
        }

        // Find new direction/rotation from Hand pointing to impact point in world.
        FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();

        FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
        GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
    }

    StopAction(InstigatorCharacter);
}