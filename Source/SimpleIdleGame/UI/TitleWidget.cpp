#include "TitleWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UTitleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Btn_SinglePlay)
		Btn_SinglePlay->OnClicked.AddDynamic(this, &UTitleWidget::OnClickSinglePlay);
    
	if (Btn_MultiPlay)
		Btn_MultiPlay->OnClicked.AddDynamic(this, &UTitleWidget::OnClickMultiPlay);
	
	if (Btn_Exit)
		Btn_Exit->OnClicked.AddDynamic(this, &UTitleWidget::OnClickExit);

	m_ElapsedTime = 0.0f;
	m_FadeInAlpha = 1.0f;
	m_FadeStage = EFadeStage::WaitBeforeLogoIn;

	if (LogoBgImage)
		LogoBgImage->SetRenderOpacity(m_FadeInAlpha);

	if (RootUIGroup)
	{
		RootUIGroup->SetRenderOpacity(1.0f);
		RootUIGroup->SetVisibility(ESlateVisibility::Visible);
		RootUIGroup->SetIsEnabled(false);
	}
}

void UTitleWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	m_ElapsedTime += InDeltaTime;

	switch (m_FadeStage)
	{
	case EFadeStage::WaitBeforeLogoIn:
		if (m_ElapsedTime >= 1.5f)
		{
			m_ElapsedTime = 0.0f;
			m_FadeStage = EFadeStage::FadeInLogo;
		}
		break;

	case EFadeStage::FadeInLogo:
		{
			m_FadeInAlpha = FMath::Clamp(m_ElapsedTime / 1.0f, 0.0f, 1.0f);
			
			if (m_FadeInAlpha >= 1.0f)
			{
				m_ElapsedTime = 0.0f;
				m_FadeStage = EFadeStage::FadeOutGroup;
			}
			break;
		}

	case EFadeStage::FadeOutGroup:
		{
			float fadeOutAlpha = FMath::Clamp(1.0f - (m_ElapsedTime / 1.0f), 0.0f, 1.0f);
			if (LogoBgImage)
				LogoBgImage->SetRenderOpacity(fadeOutAlpha);
			
			if (RootUIGroup)
				RootUIGroup->SetRenderOpacity(fadeOutAlpha);

			if (fadeOutAlpha <= 0.0f)
			{
				m_FadeStage = EFadeStage::Done;
			}
			break;
		}

	case EFadeStage::Done:
		RootUIGroup->SetVisibility(ESlateVisibility::Collapsed);
		LogoBgImage->SetVisibility(ESlateVisibility::Collapsed);
		break;
	}
}

void UTitleWidget::OnClickSinglePlay()
{
	UE_LOG(LogTemp, Log, TEXT("싱글플레이"));
	UGameplayStatics::OpenLevel(this, TEXT("SinglePlayMapName")); // 실제 맵 이름으로 바꿔줘
}

void UTitleWidget::OnClickMultiPlay()
{
	UE_LOG(LogTemp, Log, TEXT("멀티플레이"));
	UGameplayStatics::OpenLevel(this, TEXT("MultiPlayMapName")); // 실제 맵 이름으로 바꿔줘
}

void UTitleWidget::OnClickExit()
{
	UE_LOG(LogTemp, Log, TEXT("게임 종료"));
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}