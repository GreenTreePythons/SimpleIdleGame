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
	if (FMath::IsNearlyZero(Value)) return;
	
	APawn* ControlledPawn  = GetPawn();
	if (!ControlledPawn ) return;
	
	const FVector InputDirection = FVector(0.f, 1.f, 0.f);
	const FVector WorldDirection = ControlledPawn->GetActorRotation().RotateVector(InputDirection * Value);

	FRotator TargetRotation = InputDirection.Rotation();
	FRotator CurrentRotation = ControlledPawn->GetActorRotation();
	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 10.f);

	ControlledPawn->SetActorRotation(NewRotation);
	ControlledPawn->AddMovementInput(WorldDirection.GetSafeNormal(), 1.f);
}

void APlayerActorController::MoveRight(float Value)
{
	if (FMath::IsNearlyZero(Value)) return;
	
	APawn* ControlledPawn  = GetPawn();
	if (!ControlledPawn ) return;
	
	const FVector InputDirection = FVector(1.f, 0.f, 0.f);
	const FVector WorldDirection = ControlledPawn->GetActorRotation().RotateVector(InputDirection * Value);

	FRotator TargetRotation = InputDirection.Rotation();
	FRotator CurrentRotation = ControlledPawn->GetActorRotation();
	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 10.f);

	ControlledPawn->SetActorRotation(NewRotation);
	ControlledPawn->AddMovementInput(WorldDirection.GetSafeNormal(), 1.f);
}

void APlayerActorController::MoveCharacterWithJoystick(FVector2D direction)
{
	if (direction.Size() > 0.0f)
	{
		// 캐릭터 이동 방향 계산
		FVector ForwardDirection = FVector(direction.X, direction.Y, 0.0f);
		APawn* ControlledPawn = GetPawn();
		if (ControlledPawn)
		{
			ControlledPawn->AddMovementInput(ForwardDirection, 1.0f);
		}
	}
}