#include "StageGameMode.h"

AStageGameMode::AStageGameMode()
{
	DefaultPawnClass = nullptr;
}

void AStageGameMode::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("스테이지 시작"));

	SpawnPlayerCharacter();
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