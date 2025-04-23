#include "StageGameMode.h"
#include "Blueprint/UserWidget.h"
#include "IngameWidget.h"
#include "PlayerActor.h"
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
			APlayerActor* PlayerActor = Cast<APlayerActor>(PlayerCharacter);
			if (PlayerActor)
			{
				UE_LOG(LogTemp, Warning, TEXT("Set Player actor"));
				PC->Possess(Cast<APawn>(PlayerActor));
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
	if (!PC) return;

	APawn* PlayerPawn = PC->GetPawn();
	if (!PlayerPawn) return;
	
	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	FVector CameraLocation = PlayerLocation + FVector(-500.f, 0.f, 600.f);
	FRotator CameraRotation = FRotator(-45.f, 0.f, 0.f);

	// 카메라 생성
	ACameraActor* FixedCamera = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass(), CameraLocation, CameraRotation);
	if (FixedCamera)
	{
		PC->SetViewTarget(FixedCamera); // 컨트롤러가 이 카메라를 시점으로 삼게 함
		UE_LOG(LogTemp, Log, TEXT("Set independent camera"));
	}
}