// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "Components/ARInteractionComponent.h"
#include "DrawDebugHelpers.h"
#include "Interaction/ARGameplayInterface.h"
#include "UI/ARWorldUserWidget.h"

static TAutoConsoleVariable<bool> CVarDebugDrawInteraction(
    TEXT("ar.InteractionDebugDraw"), false, TEXT("Enable Debug Lines for Interact Component."), ECVF_Cheat);

UARInteractionComponent::UARInteractionComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    TraceDistance = 1000.0f;
    TraceRadius = 30.0f;
    CollisionChannel = ECC_WorldDynamic;
}

void UARInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    FindBestInteractable();
}

void UARInteractionComponent::FindBestInteractable()
{
    bool bDebugDraw = CVarDebugDrawInteraction.GetValueOnGameThread();

    FCollisionObjectQueryParams ObjectQueryParams;
    ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel);

    AActor* MyOwner = GetOwner();

    FVector EyeLocation;
    FRotator EyeRotation;

    MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

    FVector End = EyeLocation + (EyeRotation.Vector() * TraceDistance);

    TArray<FHitResult> Hits;

    FCollisionShape Shape;
    Shape.SetSphere(TraceRadius);

    bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);

    FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

    // Clear ref before trying to fill
    FocusedActor = nullptr;

    for (FHitResult Hit : Hits)
    {
        if (bDebugDraw)
        {
            DrawDebugSphere(GetWorld(), Hit.ImpactPoint, TraceRadius, 32, LineColor, false, 3.0f);
        }

        AActor* HitActor = Hit.GetActor();
        if (HitActor)
        {
            if (HitActor->Implements<UARGameplayInterface>())
            {
                FocusedActor = HitActor;
                break;
            }
        }
    }

    if (FocusedActor)
    {
        if (DefaultWidgetInstance == nullptr && ensure(DefaultWidgetClass))
        {
            DefaultWidgetInstance = CreateWidget<UARWorldUserWidget>(GetWorld(), DefaultWidgetClass);
        }

        if (DefaultWidgetInstance)
        {
            DefaultWidgetInstance->AttachedActor = FocusedActor;

            if (!DefaultWidgetInstance->IsInViewport())
            {
                DefaultWidgetInstance->AddToViewport();
            }
        }
    }
    else
    {
        if (DefaultWidgetInstance)
        {
            DefaultWidgetInstance->RemoveFromParent();
        }
    }

    if (bDebugDraw)
    {
        DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);
    }
}

void UARInteractionComponent::PrimaryInteract()
{
    if (FocusedActor == nullptr)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "No Focus Actor to interact.");
        return;
    }

    APawn* MyPawn = Cast<APawn>(GetOwner());

    IARGameplayInterface::Execute_Interact(FocusedActor, MyPawn);
}