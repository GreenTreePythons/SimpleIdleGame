// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerActorController.h"

APlayerActorController::APlayerActorController()
{
	bShowMouseCursor = true;
	UE_LOG(LogTemp, Error, TEXT(">>> PlayerActorController())"));
}

void APlayerActorController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UE_LOG(LogTemp, Warning, TEXT(">>> OnPossess: Pawn possessed"));

	SetupInputComponent();
}

void APlayerActorController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UE_LOG(LogTemp, Error, TEXT(">>> SetupInputComponent())"));
    
	// 조이스틱 입력을 설정합니다.
	InputComponent->BindAxis("MoveForward", this, &APlayerActorController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerActorController::MoveRight);
}

void APlayerActorController::MoveForward(float Value)
{
	APawn* ControlledPawn  = GetPawn();
	if (ControlledPawn )
	{
		FVector Direction = FRotationMatrix(ControlledPawn ->GetActorRotation()).GetUnitAxis(EAxis::X);
		ControlledPawn ->AddMovementInput(Direction, Value);
	}
}

void APlayerActorController::MoveRight(float Value)
{
	APawn* ControlledPawn  = GetPawn();
	if (ControlledPawn )
	{
		FVector Direction = FRotationMatrix(ControlledPawn ->GetActorRotation()).GetUnitAxis(EAxis::Y);
		ControlledPawn ->AddMovementInput(Direction, Value);
	}
}