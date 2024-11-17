// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARTargetDummy.generated.h"

class UARAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API AARTargetDummy : public AActor
{
    GENERATED_BODY()

  public:
    AARTargetDummy();

  protected:
    UPROPERTY(VisibleAnywhere)
    UARAttributeComponent *AttributeComp;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent *MeshComp;

    UFUNCTION()
    void OnHealthChanged(AActor *InstigatorActor, UARAttributeComponent *OwningComp, float NewHealth, float Delta);
};
