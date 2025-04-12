// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JoystickPanelWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEIDLEGAME_API UJoystickPanelWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;
	virtual FReply NativeOnTouchMoved(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;
	virtual FReply NativeOnTouchEnded(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;

	// 외부 접근용
	FVector2D GetJoystickDirection() const { return m_NormalizedDirection; }
	bool IsTouching() const { return m_bIsTouching; }

protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* JoystickBG;

	UPROPERTY(meta = (BindWidget))
	class UImage* Joystick;

private:
	FVector2D m_StartTouchPosition;
	FVector2D m_CurrentTouchPosition;
	FVector2D m_NormalizedDirection;
	bool m_bIsTouching = false;

	float m_JoystickRadius;
};
