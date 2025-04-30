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

	// SetupInputComponent();
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
	// 조이스틱 방향이 없다면 리턴
	if (direction.Size() <= 0.0f) return;

	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn) return;

	// 조이스틱 방향을 FVector로 변환 (Z축은 0)
	FVector ForwardDirection = FVector(direction.X, direction.Y, 0.0f);
	
	// 이동: AddMovementInput은 기본적으로 로컬 좌표계 기준으로 이동 방향을 처리
	ControlledPawn->AddMovementInput(ForwardDirection, 1.0f);
}