#include "StageGameMode.h"
#include "Blueprint/UserWidget.h"
#include "IngameWidget.h"
#include "PlayerActorController.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

AStageGameMode::AStageGameMode()
{
	DefaultPawnClass = nullptr;
	PlayerControllerClass = APlayerActorController::StaticClass();
}

void AStageGameMode::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("스테이지 시작"));

	SpawnPlayerCharacter();
	SetCamera();
	SetIngameWidget();
}

void AStageGameMode::SpawnPlayerCharacter()
{
	UClass* PlayerCharacterClass = LoadObject<UClass>(nullptr, TEXT("/Game/Characters/Farmer/Characters/Character_BP/Farmer_BP.Farmer_BP_C"));
	if (PlayerCharacterClass)
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if (PC)
		{
			FVector SpawnLocation = FVector(0.f, 0.f, 100.f);
			FRotator SpawnRotation = FRotator::ZeroRotator;

			AActor* PlayerCharacter = GetWorld()->SpawnActor<AActor>(PlayerCharacterClass, SpawnLocation, SpawnRotation);
            
			if (PlayerCharacter)
			{
				PC->Possess(Cast<APawn>(PlayerCharacter));
			}
		}
	}
}

void AStageGameMode::SetIngameWidget()
{
	TSubclassOf<UUserWidget> WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Widgets/WBP_IngameWidget.WBP_IngameWidget_C"));
	if (WidgetClass)
	{
		// UUserWidget* IngameWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
		UIngameWidget* IngameWidget = Cast<UIngameWidget>(CreateWidget<UUserWidget>(GetWorld(), WidgetClass));
		if (IngameWidget)
		{
			IngameWidget->AddToViewport();
			UE_LOG(LogTemp, Log, TEXT("IngameWidget 뷰포트에 추가 완료"));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("IngameWidget 뷰포트에 추가 실패"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("IngameWidget 로드 실패"));
	}
}

void AStageGameMode::SetCamera()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		AActor* CameraActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass());
		if (CameraActor)
		{
			PC->SetViewTarget(CameraActor); // 카메라를 플레이어 컨트롤러에 설정
		}
	}
}