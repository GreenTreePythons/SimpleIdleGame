// Fill out your copyright notice in the Description page of Project Settings.


#include "IngameWidget.h"
#include "JoystickPanelWidget.h"
#include "PlayerActorController.h"
#include "Components/CanvasPanelSlot.h"

void UIngameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 초기화 로직 필요시 작성
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		// 마우스 커서 항상 보이게
		PC->bShowMouseCursor = true;

		// UI와 게임을 둘 다 입력받도록 설정
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(false);
		InputMode.SetWidgetToFocus(nullptr);
		PC->SetInputMode(InputMode);
	}
}

void UIngameWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
    
    if (IsUsingJoystick())
    {
        APlayerActorController* PlayerController = Cast<APlayerActorController>(GetWorld()->GetFirstPlayerController());
        if (PlayerController)
        {
            PlayerController->MoveCharacterWithJoystick(GetJoystickDirection());
        }
    }
}

FVector2D UIngameWidget::GetJoystickDirection() const
{
	return IsUsingJoystick() ? JoystickPanelWidget->GetJoystickDirection() : FVector2D::ZeroVector;
}

bool UIngameWidget::IsUsingJoystick() const
{
	return JoystickPanelWidget && JoystickPanelWidget->IsTouching();
}