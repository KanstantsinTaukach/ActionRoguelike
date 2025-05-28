// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "Actions/ARAction.h"
#include "CoreMinimal.h"
#include "ARAction_ProjectileAttack.generated.h"

class UAnimMontage;
class UParticleSystem;

UCLASS()
class ACTIONROGUELIKE_API UARAction_ProjectileAttack : public UARAction
{
    GENERATED_BODY()

  protected:
    UPROPERTY(EditAnywhere, Category = "Attack")
    TSubclassOf<AActor> ProjectileClass;

    UPROPERTY(EditAnywhere, Category = "Attack")
    UAnimMontage *AttackAnim;

    UPROPERTY(EditAnywhere, Category = "Attack")
    UParticleSystem *CastingEffect;

    UPROPERTY(EditDefaultsOnly, Category = "Attack")
    float AttackAnimDelay;

    UPROPERTY(VisibleAnywhere, Category = "Effects")
    FName HandSocketName;

    UFUNCTION()
    void AttackDelay_Elapsed(ACharacter *InstigatorCharacter);

  public:
    UARAction_ProjectileAttack();

    virtual void StartAction_Implementation(AActor *Instigator) override;
};
