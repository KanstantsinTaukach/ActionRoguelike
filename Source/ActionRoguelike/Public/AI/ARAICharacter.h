// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARAICharacter.generated.h"

class UPawnSensingComponent;

UCLASS()
class ACTIONROGUELIKE_API AARAICharacter : public ACharacter
{
    GENERATED_BODY()

  public:
    AARAICharacter();

  protected:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UPawnSensingComponent *PawnSensingComp;

    UFUNCTION()
    void OnPawnSeen(APawn *Pawn);

    virtual void PostInitializeComponents() override;
};
