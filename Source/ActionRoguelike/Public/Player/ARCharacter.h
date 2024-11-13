// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapon/ARMagicProjectile.h"
#include "ARCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UARInteractionComponent;
class UAnimMontage;
class UARAttributeComponent;

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

    UPROPERTY(VisibleAnywhere)
    UARInteractionComponent *InteractionComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UARAttributeComponent *AttributeComp;

    UPROPERTY(EditAnywhere, Category = "Attack")
    TSubclassOf<AARMagicProjectile> ProjectileClass;

    UPROPERTY(EditAnywhere, Category = "Attack")
    UAnimMontage *AttackAnim;

    FTimerHandle TimerHandle_PrimaryAttack;

    virtual void BeginPlay() override;

    void MoveForward(float Value);

    void MoveRight(float Value);

    void PrimaryAttack();

    void PrimaryAttack_TimeElapsed();

    void PrimaryInteract();

  public:
    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
};
