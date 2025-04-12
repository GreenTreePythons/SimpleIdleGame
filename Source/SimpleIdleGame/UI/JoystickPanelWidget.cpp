// Fill out your copyright notice in the Description page of Project Settings.


#include "JoystickPanelWidget.h"
#include "Components/Image.h"

void UJoystickPanelWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_NormalizedDirection = FVector2D::ZeroVector;
	m_bIsTouching = false;

	if (Joystick)
	{
		Joystick->SetRenderTranslation(FVector2D::ZeroVector);
	}

	if (JoystickBG)
	{
		FVector2D size = JoystickBG->GetDesiredSize();
		m_JoystickRadius = size.X * 0.5f;
	}
}

FReply UJoystickPanelWidget::NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	m_bIsTouching = true;
	m_StartTouchPosition = InGestureEvent.GetScreenSpacePosition();
	m_CurrentTouchPosition = m_StartTouchPosition;
	return FReply::Handled();
}

FReply UJoystickPanelWidget::NativeOnTouchMoved(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	m_CurrentTouchPosition = InGestureEvent.GetScreenSpacePosition();
	FVector2D delta = m_CurrentTouchPosition - m_StartTouchPosition;
	float distance = FMath::Min(delta.Size(), m_JoystickRadius);
	FVector2D direction = delta.GetSafeNormal();

	m_NormalizedDirection = direction;

	if (Joystick)
	{
		Joystick->SetRenderTranslation(direction * distance);
	}

	return FReply::Handled();
}

FReply UJoystickPanelWidget::NativeOnTouchEnded(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	m_bIsTouching = false;
	m_NormalizedDirection = FVector2D::ZeroVector;

	if (Joystick)
	{
		Joystick->SetRenderTranslation(FVector2D::ZeroVector);
	}

	return FReply::Handled();
}