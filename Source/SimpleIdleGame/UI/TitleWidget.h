#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidget.generated.h"

UCLASS()
class SIMPLEIDLEGAME_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void OnClickSinglePlay();

	UFUNCTION()
	void OnClickMultiPlay();

	UFUNCTION()
	void OnClickExit();

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_SinglePlay;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_MultiPlay;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Exit;

	UPROPERTY(meta = (BindWidget))
	class UOverlay* RootUIGroup;
	
	UPROPERTY(meta = (BindWidget))
	class UImage* LogoBgImage;

private:
	float m_FadeInAlpha = 0.0f;
	float m_ElapsedTime = 0.0f;
	enum class EFadeStage
	{
		WaitBeforeLogoIn,
		FadeInLogo,
		FadeOutGroup,
		Done
	};

	EFadeStage m_FadeStage = EFadeStage::WaitBeforeLogoIn;
};