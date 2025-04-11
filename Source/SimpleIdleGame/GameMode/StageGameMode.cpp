// Fill out your copyright notice in the Description page of Project Settings.


#include "StageGameMode.h"

AStageGameMode::AStageGameMode()
{
	DefaultPawnClass = nullptr;
}

void AStageGameMode::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("스테이지 시작"));

	// SpawnPlayerCharacter();
}

void AStageGameMode::SpawnPlayerCharacter()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerCharacterClass(TEXT("/Game/Characters/Farmer/Characters/Character_BP/Farmer_BP"));
    
	if (PlayerCharacterClass.Succeeded())
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if (PC)
		{
			FVector SpawnLocation = FVector(0.f, 0.f, 100.f);
			FRotator SpawnRotation = FRotator::ZeroRotator;

			AActor* PlayerCharacter = GetWorld()->SpawnActor<AActor>(PlayerCharacterClass.Class, SpawnLocation, SpawnRotation);
            
			if (PlayerCharacter)
			{
				PC->Possess(Cast<APawn>(PlayerCharacter));
				UE_LOG(LogTemp, Log, TEXT("플레이어 캐릭터 스폰 완료"));
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Farmer_BP 블루프린트를 로드하는 데 실패했습니다!"));
	}
}