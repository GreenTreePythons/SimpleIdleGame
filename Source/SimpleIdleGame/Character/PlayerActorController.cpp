// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerActorController.h"

APlayerActorController::APlayerActorController()
{
	bShowMouseCursor = false;
}

void APlayerActorController::SetupInputComponent()
{
	Super::SetupInputComponent();
    
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