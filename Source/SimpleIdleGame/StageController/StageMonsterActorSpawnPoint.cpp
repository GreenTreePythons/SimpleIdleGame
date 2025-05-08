// StageMonsterActorSpawnPoint.cpp

#include "StageMonsterActorSpawnPoint.h"
#include "Engine/World.h"
#include "MonsterActor.h"
#include "DrawDebugHelpers.h"  // DrawDebug 관련 함수들

AStageMonsterActorSpawnPoint::AStageMonsterActorSpawnPoint()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AStageMonsterActorSpawnPoint::SpawnMonsters(int32 StageLevel)
{
	FString MonsterSID = FString::Printf(TEXT("Monster_%d"), StageLevel);  // SID를 스테이지 레벨로 설정

	// 데이터 테이블에서 몬스터 정보 로드
	if (MonsterStatsTable)
	{
		FMonsterActorInformation* MonsterData = MonsterStatsTable->FindRow<FMonsterActorInformation>(FName(*MonsterSID), TEXT(""));

		if (MonsterData)
		{
			// 몬스터 스텟을 바탕으로 몬스터를 스폰
			for (int32 i = 0; i < SpawnCount; ++i)
			{
				if (MonsterToSpawn)
				{
					GetWorld()->SpawnActor<AMonsterActor>(MonsterToSpawn, GetActorLocation(), GetActorRotation());
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("cant find Monster_%d"), StageLevel);
		}
	}
}

void AStageMonsterActorSpawnPoint::ActivateSpawnPoint(int32 StageLevel)
{
	// 데이터 테이블에서 SID에 맞는 몬스터 스텟을 가져와서 소환
	SpawnMonsters(StageLevel);  // StageLevel에 맞는 몬스터 스폰
}

void AStageMonsterActorSpawnPoint::DeactivateSpawnPoint()
{
	// 스폰 포인트 비활성화
	UE_LOG(LogTemp, Log, TEXT("Spawn Point Deactivated"));
}

void AStageMonsterActorSpawnPoint::SetSpawnCount(int32 NewSpawnCount)
{
	SpawnCount = NewSpawnCount;
}

void AStageMonsterActorSpawnPoint::SetMonsterToSpawn(TSubclassOf<AMonsterActor> NewMonsterClass)
{
	MonsterToSpawn = NewMonsterClass;
}