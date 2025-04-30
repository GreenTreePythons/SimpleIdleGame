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
	
	PrimaryActorTick.bCanEverTick = true;
}

void AStageGameMode::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("스테이지 시작"));

	SpawnPlayerCharacter();
	SetCamera();
	SetIngameWidget();
}

void AStageGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateCameraPos();
}

void AStageGameMode::SpawnPlayerCharacter()
{
	UClass* PlayerCharacterClass = LoadObject<UClass>(nullptr, TEXT("/Game/Characters/Farmer/Characters/Character_BP/Farmer_BP.Farmer_BP_C"));
	if (!PlayerCharacterClass) return;
	
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return;
	
	FVector SpawnLocation = FVector(0.f, 0.f, 100.f);
	FRotator SpawnRotation = FRotator::ZeroRotator;

	AActor* PlayerCharacter = GetWorld()->SpawnActor<AActor>(PlayerCharacterClass, SpawnLocation, SpawnRotation);
	APlayerActor* PlayerActor = Cast<APlayerActor>(PlayerCharacter);
	if (!PlayerActor) return;
	
	UE_LOG(LogTemp, Warning, TEXT("Set Player actor"));
	PC->Possess(Cast<APawn>(PlayerActor));
}

void AStageGameMode::SetIngameWidget()
{
	TSubclassOf<UUserWidget> WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Widgets/WBP_IngameWidget.WBP_IngameWidget_C"));
	if (!WidgetClass) return;
	
	UIngameWidget* IngameWidget = Cast<UIngameWidget>(CreateWidget<UUserWidget>(GetWorld(), WidgetClass));
	if (!IngameWidget) return;
	
	IngameWidget->AddToViewport();
}

void AStageGameMode::SetCamera()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return;

	APawn* PlayerPawn = PC->GetPawn();
	if (!PlayerPawn) return;

	FollowCamera = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
	if (!FollowCamera) return;
	
	PC->SetViewTarget(FollowCamera);
	UE_LOG(LogTemp, Log, TEXT("Set independent camera"));
}

void AStageGameMode::UpdateCameraPos()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC || !FollowCamera) return;

	APawn* PlayerPawn = PC->GetPawn();
	if (!PlayerPawn) return;

	const FVector PlayerLocation = PlayerPawn->GetActorLocation();
	const FVector Offset = FVector(-500.f, 0.f, 800.f);
	FollowCamera->SetActorLocation(PlayerLocation + Offset);
	FollowCamera->SetActorRotation(FRotator(-60.f, 0.f, 0.f));
}
