// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerActor.h"

#include "PlayerActorAnimInstance.h"

// Sets default values
APlayerActor::APlayerActor()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// CameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CameraRoot"));
	// CameraRoot->SetupAttachment(RootComponent);
	// CameraRoot->SetUsingAbsoluteLocation(false);
	// CameraRoot->SetUsingAbsoluteRotation(true);
	//
	// FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// FollowCamera->SetupAttachment(CameraRoot);
	// FollowCamera->SetRelativeLocation(FVector(0.f, 0.f, 500.f));
	// FollowCamera->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	//
	// FollowCamera->bUsePawnControlRotation = false;  // 카메라가 회전하지 않게 설정
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
}

// Called to bind functionality to input
void APlayerActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

