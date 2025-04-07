// Fill out your copyright notice in the Description page of Project Settings.

#include "TitleGameMode.h"
#include "TitleHUD.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

ATitleGameMode::ATitleGameMode()
{
	HUDClass = ATitleHUD::StaticClass();
	DefaultPawnClass = nullptr;
	
}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		UE_LOG(LogTemp, Warning, TEXT("[TitleGameMode] PlayerController obtained: %s"), *PC->GetName());
		AActor* CameraActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass());
		if (CameraActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("[TitleGameMode] Setting ViewTarget to CameraActor: %s"), *CameraActor->GetName());
			PC->SetViewTarget(CameraActor);
		}
	}
}