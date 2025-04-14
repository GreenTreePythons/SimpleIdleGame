#include "JoystickPanelWidget.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"

void UJoystickPanelWidget::NativeConstruct()
{
    Super::NativeConstruct();

    m_NormalizedDirection = FVector2D::ZeroVector;
    m_bIsTouching = false;

    if (Joystick)
    {
        Joystick->SetRenderTranslation(FVector2D::ZeroVector);
    }

    UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(JoystickBG->Slot);
    if (CanvasSlot)
    {
        FVector2D size = CanvasSlot->GetSize();
        m_JoystickRadius = size.X * 0.5f;
    }
}

FReply UJoystickPanelWidget::NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
    UE_LOG(LogTemp, Log, TEXT(">>>NativeOnTouchStarted"));
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
    UE_LOG(LogTemp, Log, TEXT(">>>NativeOnTouchEnded"));
    ResetJoystickPosition();
    return FReply::Handled();
}

FReply UJoystickPanelWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    UE_LOG(LogTemp, Log, TEXT(">>>NativeOnMouseButtonDown"));
    m_bIsTouching = true;
    m_StartTouchPosition = InMouseEvent.GetScreenSpacePosition();
    m_CurrentTouchPosition = m_StartTouchPosition;
    return FReply::Handled();
}

FReply UJoystickPanelWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (m_bIsTouching)  // 마우스 버튼이 눌린 상태일 때만 이동 처리
    {
        return HandleInputMove(InMouseEvent.GetScreenSpacePosition());
    }

    return FReply::Unhandled();
}

FReply UJoystickPanelWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    UE_LOG(LogTemp, Log, TEXT(">>>NativeOnMouseButtonUp"))
    ResetJoystickPosition();
    return FReply::Handled();
}

// 마우스와 터치 입력을 공통으로 처리
FReply UJoystickPanelWidget::HandleInputMove(FVector2D CurrentPosition)
{
    FVector2D delta = CurrentPosition - m_StartTouchPosition;
    float distance = FMath::Min(delta.Size(), m_JoystickRadius);
    FVector2D direction = delta.GetSafeNormal();

    m_NormalizedDirection = direction;

    if (Joystick)
    {
        UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Joystick->Slot);
        if (CanvasSlot)
        {
            CanvasSlot->SetPosition(direction * distance);  
        }
    }

    return FReply::Handled();
}

bool UJoystickPanelWidget::IsPointerOutside() const
{
    if (!JoystickBG) return false;  // JoystickBG가 없으면 처리하지 않음
    
    // 마우스 위치 받아오기
    FVector2D MousePos;
    
    if (GetWorld()->GetFirstPlayerController()->GetMousePosition(MousePos.X, MousePos.Y))
    {
        // X와 Y 값을 각각 출력
        UE_LOG(LogTemp, Log, TEXT("Mouse Position: X: %f, Y: %f"), MousePos.X, MousePos.Y);
    }
    
    if (!GetWorld()->GetFirstPlayerController()->GetMousePosition(MousePos.X, MousePos.Y))
        return false;

    // JoystickBG의 위치와 크기를 받아옵니다.
    UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(JoystickBG->Slot);
    if (CanvasSlot)
    {
        FVector2D BGPosition = CanvasSlot->GetPosition();
        FVector2D BGSize = CanvasSlot->GetSize();

        // Joystick이 배치된 영역의 중심과 크기
        FVector2D JoystickCenter = BGPosition + BGSize * 0.5f;

        // 마우스와 조이스틱 중심 간의 거리 계산
        FVector2D Distance = MousePos - JoystickCenter;

        // 마우스가 반경을 벗어났는지 체크
        return Distance.Size() > m_JoystickRadius;
    }

    return false;
}

void UJoystickPanelWidget::ResetJoystickPosition()
{
    m_bIsTouching = false;
    m_NormalizedDirection = FVector2D::ZeroVector;
    if (Joystick)
    {
        UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Joystick->Slot);
        if (CanvasSlot)
        {
            CanvasSlot->SetPosition(FVector2d::ZeroVector);  
        }
    }
}
