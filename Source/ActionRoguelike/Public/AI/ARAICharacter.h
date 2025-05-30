// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARAICharacter.generated.h"

class UPawnSensingComponent;
class UARAttributeComponent;
class UARActionComponent;
class UARWorldUserWidget;
class UUserWidget;

UCLASS()
class ACTIONROGUELIKE_API AARAICharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AARAICharacter();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UPawnSensingComponent* PawnSensingComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UARAttributeComponent* AttributeComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UARActionComponent* ActionComp;

    UPROPERTY(VisibleAnywhere, Category = "Effects")
    FName TimeToHitParamName;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> HealthBarWidgetClass;

    UARWorldUserWidget* ActiveHealthBar;

    UFUNCTION()
    void OnPawnSeen(APawn* Pawn);

    UFUNCTION()
    void OnHealthChanged(AActor* InstigatorActor, UARAttributeComponent* OwningComp, float NewHealth, float Delta);

    virtual void PostInitializeComponents() override;

    void SetTargetActor(AActor* NewTarget);
};
