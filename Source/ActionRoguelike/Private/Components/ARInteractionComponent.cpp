// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "Components/ARInteractionComponent.h"
#include "DrawDebugHelpers.h"
#include "Interaction/ARGameplayInterface.h"

UARInteractionComponent::UARInteractionComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UARInteractionComponent::PrimaryInteract()
{
    FCollisionObjectQueryParams ObjectQueryParams;
    ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

    AActor *MyOwner = GetOwner();

    FVector EyeLocation;
    FRotator EyeRotation;

    MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

    FVector End = EyeLocation + (EyeRotation.Vector() * 1000.0f);

    // FHitResult Hit;
    // bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);

    // AActor *HitActor = Hit.GetActor();
    // if (HitActor)
    // {
    //     if (HitActor->Implements<UARGameplayInterface>())
    //     {
    //         APawn *MyPawn = Cast<APawn>(MyOwner);

    //         IARGameplayInterface::Execute_Interact(HitActor, MyPawn);
    //     }
    // }

    // FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;
    // DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);

    TArray<FHitResult> Hits;

    float Radius = 30.0f;

    FCollisionShape Shape;
    Shape.SetSphere(Radius);

    bool bBlockingHit =
        GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);

    FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

    for (FHitResult Hit : Hits)
    {
        AActor *HitActor = Hit.GetActor();
        if (HitActor)
        {
            if (HitActor->Implements<UARGameplayInterface>())
            {
                APawn *MyPawn = Cast<APawn>(MyOwner);

                IARGameplayInterface::Execute_Interact(HitActor, MyPawn);

                DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor, false, 3.0f);

                break;
            }
        }
    }

    DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);
}

void UARInteractionComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UARInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
