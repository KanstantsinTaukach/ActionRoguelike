// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "ARInteractionComponent.generated.h"

class UARWorldUserWidget;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API UARInteractionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UARInteractionComponent();

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void PrimaryInteract();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Trace")
    float TraceDistance;

    UPROPERTY(EditDefaultsOnly, Category = "Trace")
    float TraceRadius;

    UPROPERTY(EditDefaultsOnly, Category = "Trace")
    TEnumAsByte<ECollisionChannel> CollisionChannel;

    UPROPERTY()
    AActor* FocusedActor;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UARWorldUserWidget> DefaultWidgetClass;

    UPROPERTY()
    UARWorldUserWidget* DefaultWidgetInstance;

    void FindBestInteractable();

    // Reliable - will always arrive, eventually. Request will be re-sent unless an acknowledgment was received.
    // Unreliable - not guaranteed, packet can get lost and wont't retry.

    UFUNCTION(Server, Reliable)
    void ServerInteract(AActor* InFocus);
};
