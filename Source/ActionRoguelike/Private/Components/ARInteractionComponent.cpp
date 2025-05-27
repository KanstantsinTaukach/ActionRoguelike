// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "Components/ARInteractionComponent.h"
#include "DrawDebugHelpers.h"
#include "Interaction/ARGameplayInterface.h"

static TAutoConsoleVariable<bool> CVarDebugDrawInteraction(TEXT("ar.InteractionDebugDraw"), false, TEXT("Enable Debug Lines for Interact Component."), ECVF_Cheat);

UARInteractionComponent::UARInteractionComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UARInteractionComponent::PrimaryInteract()
{
    bool bDebugDraw = CVarDebugDrawInteraction.GetValueOnGameThread();

    FCollisionObjectQueryParams ObjectQueryParams;
    ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

    AActor *MyOwner = GetOwner();

    FVector EyeLocation;
    FRotator EyeRotation;

    MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

    FVector End = EyeLocation + (EyeRotation.Vector() * 1000.0f);

    TArray<FHitResult> Hits;

    float Radius = 30.0f;

    FCollisionShape Shape;
    Shape.SetSphere(Radius);

    bool bBlockingHit =
        GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);

    FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

    for (FHitResult Hit : Hits)
    {
        if (bDebugDraw)
        {
            DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor, false, 3.0f);
        }

        AActor *HitActor = Hit.GetActor();
        if (HitActor)
        {
            if (HitActor->Implements<UARGameplayInterface>())
            {
                APawn *MyPawn = Cast<APawn>(MyOwner);

                IARGameplayInterface::Execute_Interact(HitActor, MyPawn);
                break;
            }
        }
    }

    if (bDebugDraw)
    {
        DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);
    }
}