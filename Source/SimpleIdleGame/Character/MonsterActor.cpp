// MonsterActor.cpp
#include "MonsterActor.h"

AMonsterActor::AMonsterActor()
{
	PrimaryActorTick.bCanEverTick = true;
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

void AMonsterActor::LoadMonsterData(const FString& SID)
{
	// 데이터 테이블에서 SID에 맞는 몬스터 정보 로드
	static const FString ContextString(TEXT("Monster Info Context"));
	FMonsterActorInformation* MonsterInfo = MonsterStatsTable->FindRow<FMonsterActorInformation>(FName(*SID), ContextString);

	if (MonsterInfo)
	{
		// 데이터 테이블에서 불러온 몬스터 스텟 설정
		MonsterInformation = *MonsterInfo;  // FMonsterActorInformation에 정보 설정
		UE_LOG(LogTemp, Log, TEXT("Loaded Monster Data: %s"), *SID);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Monster data not found for SID: %s"), *SID);
	}
}