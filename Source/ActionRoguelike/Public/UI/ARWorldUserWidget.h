// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "ARWorldUserWidget.generated.h"

class USizeBox;

UCLASS()
class ACTIONROGUELIKE_API UARWorldUserWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (ExposeOnSpawn = true));
    AActor* AttachedActor;

protected:
    UPROPERTY(meta = (BindWidget))
    USizeBox* ParentSizeBox;

    UPROPERTY(EditAnywhere, Category = "UI")
    FVector WorldOffset;

    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
