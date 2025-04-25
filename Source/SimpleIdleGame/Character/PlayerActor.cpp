// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerActor.h"

#include "PlayerActorAnimInstance.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerActor::APlayerActor()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float Speed = GetVelocity().Size2D();

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (UPlayerActorAnimInstance* ActorAnimInstance = Cast<UPlayerActorAnimInstance>(AnimInstance))
	{
		ActorAnimInstance->ActorSpeed = Speed;
	}

	DrawDebugCoordinateSystem(
		GetWorld(),
		GetActorLocation(),
		GetActorRotation(),
		100.f,   // 축 길이
		false,   // 지속 여부
		-1.f,    // 지속 시간 (한 프레임만)
		0,       // Depth priority
		1.5f     // 두께
	);
}

// Called to bind functionality to input
void APlayerActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

