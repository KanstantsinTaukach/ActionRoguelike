// ActionRoguelike game. Copyright Taukach K. All Rights Reserved.

#include "UI/ARWorldUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SizeBox.h"

DEFINE_LOG_CATEGORY_STATIC(ARWorldUserWidgetLog, All, All);

void UARWorldUserWidget::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (!IsValid(AttachedActor))
    {
        RemoveFromParent();

        UE_LOG(ARWorldUserWidgetLog, Warning, TEXT("AttachedActor no longer valid, removing Health Widget."));
        return;
    }

    FVector2D ScreenPosition;
    if (UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), AttachedActor->GetActorLocation() + WorldOffset, ScreenPosition))
    {
        float Scale = UWidgetLayoutLibrary::GetViewportScale(this);

        ScreenPosition /= Scale;

        if (ParentSizeBox)
        {
            ParentSizeBox->SetRenderTranslation(ScreenPosition);
        }
    }
}
