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

	SpawnPlayerCharacter();
}

void AStageGameMode::SpawnPlayerCharacter()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return;

	FVector SpawnLocation = FVector(0.f, 0.f, 100.f);
	FRotator SpawnRotation = FRotator::ZeroRotator;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = PC;

	
}