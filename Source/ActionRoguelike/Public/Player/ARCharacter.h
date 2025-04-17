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

UCLASS()
class ACTIONROGUELIKE_API AARCharacter : public ACharacter
{
    GENERATED_BODY()

  public:
    AARCharacter();

    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

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
    TSubclassOf<AActor> BlackHoleProjectileClass;

    UPROPERTY(EditAnywhere, Category = "Attack")
    TSubclassOf<AARDashProjectile> DashProjectileClass;

    UPROPERTY(EditAnywhere, Category = "Attack")
    UAnimMontage *AttackAnim;

    UPROPERTY(EditAnywhere, Category = "Attack")
    UParticleSystem *CastingEffect;

    UPROPERTY(EditDefaultsOnly, Category = "Attack")
    float AttackAnimDelay;

    UPROPERTY(VisibleAnywhere, Category = "Effects")
    FName TimeToHitParamName;

    UPROPERTY(VisibleAnywhere, Category = "Effects")
    FName HandSocketName;

    FTimerHandle TimerHandle_PrimaryAttack;
    FTimerHandle TimerHandle_BlackHoleAttack;
    FTimerHandle TimerHandle_DashAttack;

    void MoveForward(float Value);

    void MoveRight(float Value);

    void PrimaryAttack();
    void PrimaryAttack_TimeElapsed();

    void BlackHoleAttack();
    void BlackHoleAttack_TimeElapsed();

    void Dash();
    void Dash_TimeElapsed();

    void StartAttackEffects();

    void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);

    void PrimaryInteract();

    virtual void PostInitializeComponents() override;

    UFUNCTION()
    void OnHealthChanged(AActor *InstigatorActor, UARAttributeComponent *OwningComp, float NewHealth, float Delta);
};
