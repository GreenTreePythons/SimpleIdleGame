#include "TitleWidget.h"
#include "Components/Button.h"
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