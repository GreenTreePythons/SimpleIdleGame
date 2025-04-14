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

	// 터치 이벤트 처리
	virtual FReply NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;
	virtual FReply NativeOnTouchMoved(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;
	virtual FReply NativeOnTouchEnded(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;

	// 마우스 이벤트 처리
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	// 외부 접근용
	FVector2D GetJoystickDirection() const { return m_NormalizedDirection; }
	bool IsTouching() const { return m_bIsTouching; }
	bool IsPointerOutside() const;
	void ResetJoystickPosition();

protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* JoystickBG;

	UPROPERTY(meta = (BindWidget))
	class UImage* Joystick;

private:
	// 터치 및 마우스 입력 처리 관련 변수
	FVector2D m_StartTouchPosition;
	FVector2D m_CurrentTouchPosition;
	FVector2D m_NormalizedDirection;
	bool m_bIsTouching = false;

	float m_JoystickRadius;

	// 입력 처리 공통 함수
	FReply HandleInputMove(FVector2D CurrentPosition);
};
