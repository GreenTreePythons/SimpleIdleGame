// MonsterActor.cpp
#include "MonsterActor.h"

AMonsterActor::AMonsterActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// 기본 몬스터 정보 객체 생성
	// MonsterInformation = CreateDefaultSubobject<FMonsterActorInformation>(TEXT("Monster Information"));
}

void AMonsterActor::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 몬스터 공격 (사정거리 기준으로 공격)
	Attack();
}

void AMonsterActor::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT(">>> Attack()"));	
}