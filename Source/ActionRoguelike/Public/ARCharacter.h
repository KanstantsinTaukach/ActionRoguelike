// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ACTIONROGUELIKE_API AARCharacter : public ACharacter
{
    GENERATED_BODY()

  public:
    AARCharacter();

  protected:
    UPROPERTY(VisibleAnywhere)
    USpringArmComponent *SpringArmComp;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent *CameraComp;

    virtual void BeginPlay() override;

    void MoveForward(float Value);

  public:
    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
};
