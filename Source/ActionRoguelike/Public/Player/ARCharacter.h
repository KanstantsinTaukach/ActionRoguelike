// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapon/ARMagicProjectile.h"
#include "Weapon/ARDashProjectile.h"
#include "ARCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UARInteractionComponent;
class UAnimMontage;
class UARAttributeComponent;
class UARActionComponent;

UCLASS()
class ACTIONROGUELIKE_API AARCharacter : public ACharacter
{
    GENERATED_BODY()

  public:
    AARCharacter();

    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

    UFUNCTION(Exec)
    void HealSelf(float Amount = 100.0f);

  protected:
    UPROPERTY(VisibleAnywhere)
    USpringArmComponent *SpringArmComp;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent *CameraComp;

    UPROPERTY(VisibleAnywhere)
    UARInteractionComponent *InteractionComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UARAttributeComponent *AttributeComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UARActionComponent *ActionComp;

    UPROPERTY(VisibleAnywhere, Category = "Effects")
    FName TimeToHitParamName;

    void MoveForward(float Value);
    void MoveRight(float Value);

    void SprintStart();
    void SprintStop();

    void PrimaryAttack();
    void BlackHoleAttack();
    void Dash();
    
    void PrimaryInteract();

    virtual void PostInitializeComponents() override;

    virtual FVector GetPawnViewLocation() const override;

    UFUNCTION()
    void OnHealthChanged(AActor *InstigatorActor, UARAttributeComponent *OwningComp, float NewHealth, float Delta);
};
