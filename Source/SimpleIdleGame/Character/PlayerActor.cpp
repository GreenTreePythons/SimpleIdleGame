// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerActor.h"

// Sets default values
APlayerActor::APlayerActor()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(RootComponent);  // 카메라를 캐릭터의 루트에 부착
	FollowCamera->bUsePawnControlRotation = false;  // 카메라가 회전하지 않게 설정

	// 애니메이션 로드
	static ConstructorHelpers::FObjectFinder<UAnimSequence> IdleAnimRef(TEXT("/Game/Characters/Farmer/Animations/Farmer/anim_Farmer_idle_basic.anim_Farmer_idle_basic"));
	if (IdleAnimRef.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT(">>> IdleAnim load succeeded"));
		IdleAnim = IdleAnimRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> RunAnimRef(TEXT("/Game/Characters/Farmer/Animations/Farmer/anim_Farmer_run.anim_Farmer_run"));
	if (RunAnimRef.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT(">>> RunAnim load succeeded"));
		RunAnim = RunAnimRef.Object;
	}
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
	// 캐릭터의 이동 속도 체크
	float Speed = GetVelocity().Size2D();
	if (Speed > 5.f) // 이동 중 (Run)
	{
		if (RunAnim && GetMesh()->GetAnimationMode() != EAnimationMode::AnimationSingleNode)
		{
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);  // 반드시 설정
		}
	
		if (RunAnim && !GetMesh()->IsPlaying())
		{
			GetMesh()->PlayAnimation(RunAnim, true);  // 반복 재생
		}
	}
	else // Idle 상태
	{
		if (IdleAnim && GetMesh()->GetAnimationMode() != EAnimationMode::AnimationSingleNode)
		{
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);  // 반드시 설정
		}
	
		if (IdleAnim && !GetMesh()->IsPlaying())
		{
			GetMesh()->PlayAnimation(IdleAnim, true);  // 반복 재생
		}
	}
}

// Called to bind functionality to input
void APlayerActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

