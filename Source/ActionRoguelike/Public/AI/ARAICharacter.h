// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARAICharacter.generated.h"

class UPawnSensingComponent;
class UARAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API AARAICharacter : public ACharacter
{
    GENERATED_BODY()

  public:
    AARAICharacter();

  protected:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UPawnSensingComponent *PawnSensingComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UARAttributeComponent *AttributeComp;

    UFUNCTION()
    void OnPawnSeen(APawn *Pawn);

    UFUNCTION()
    void OnHealthChanged(AActor *InstigatorActor, UARAttributeComponent *OwningComp, float NewHealth, float Delta);

    virtual void PostInitializeComponents() override;

    void SetTargetActor(AActor *NewTarget);
};
