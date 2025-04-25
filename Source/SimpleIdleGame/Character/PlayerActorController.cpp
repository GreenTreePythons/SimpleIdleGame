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
    
	InputComponent->BindAxis("MoveForward", this, &APlayerActorController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerActorController::MoveRight);
}

void APlayerActorController::MoveForward(float Value)
{
	if (FMath::IsNearlyZero(Value)) return;

	const FVector InputDirection = FVector(Value, 0.f, 0.f);

	Move(InputDirection);
}

void APlayerActorController::MoveRight(float Value)
{
	if (FMath::IsNearlyZero(Value)) return;
	
	const FVector InputDirection = FVector(0.f, Value, 0.f);

	Move(InputDirection);
}

void APlayerActorController::Move(FVector InputDirection)
{
	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn) return;

	const FVector MoveDirection = InputDirection.GetSafeNormal();

	FRotator TargetRotation = MoveDirection.Rotation();
	FRotator NewRotation = FMath::RInterpTo
	(
		ControlledPawn->GetActorRotation(),
		TargetRotation,
		GetWorld()->GetDeltaSeconds(),
		10.f
	);

	ControlledPawn->SetActorRotation(NewRotation);
	ControlledPawn->AddMovementInput(MoveDirection, 1.f);
}

void APlayerActorController::MoveCharacterWithJoystick(FVector2D direction)
{
	if (direction.Size() > 0.0f)
	{
		FVector ForwardDirection = FVector(direction.X, direction.Y, 0.0f);
		APawn* ControlledPawn = GetPawn();
		if (ControlledPawn)
		{
			ControlledPawn->AddMovementInput(ForwardDirection, 1.0f);
		}
	}
}