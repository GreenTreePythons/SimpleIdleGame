// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IngameWidget.generated.h"

/**
 * 
 */
class UJoystickPanelWidget;

UCLASS()
class SIMPLEIDLEGAME_API UIngameWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
	UJoystickPanelWidget* JoystickPanelWidget;

public:
	// 외부에 조이스틱 상태 전달
	FVector2D GetJoystickDirection() const;
	bool IsUsingJoystick() const;
};
