#include "StageMonsterActorSpawnPoint.h"
#include "Engine/World.h"
#include "MonsterActor.h"
#include "DrawDebugHelpers.h"  // DrawDebug 관련 함수들

UStageMonsterActorSpawnPoint::UStageMonsterActorSpawnPoint()
{
	// 기본 값 설정
	MonsterLevel = 1;  // 기본 레벨 1
	SpawnCount = 5;  // 기본 몬스터 수 5
}

void UStageMonsterActorSpawnPoint::SpawnMonsters(int32 StageLevel, UDataTable* MonsterStatsTable)
{
	// // 몬스터 스폰 로직 (활성화 상태일 때만 스폰)
	// if (bIsActive && MonsterToSpawn && MonsterLevel > 0 && SpawnCount > 0)
	// {
	// 	// 몬스터 스폰 로직은 실제 게임 오브젝트에서 처리할 것이므로, 
	// 	// 예를 들어, 몬스터 스폰 시 위치는 게임 월드 내에 정해진 지점에서 처리
	// 	FVector SpawnLocation = FVector(0.0f, 0.0f, 0.0f);  // 예시로 (0,0,0)으로 설정
	// 	FRotator SpawnRotation = FRotator::ZeroRotator;
	//
	// 	for (int32 i = 0; i < SpawnCount; ++i)
	// 	{
	// 		AMonsterActor* SpawnedMonster = GetWorld()->SpawnActor<AMonsterActor>(MonsterToSpawn, SpawnLocation, SpawnRotation);
	// 		if (SpawnedMonster)
	// 		{
	// 			// 레벨에 맞는 몬스터 스텟 설정
	// 			SpawnedMonster->MonsterInformation->SetStatsFromDataTable(MonsterStatsTable, FString::Printf(TEXT("Monster_Level_%d"), StageLevel));
	// 		}
	// 	}
	//
	// 	// 디버그용으로 스폰 위치를 박스로 표시
	// 	DrawDebugBox(GetWorld(), SpawnLocation, FVector(100.0f, 100.0f, 50.0f), FQuat::Identity, FColor::Red, true, -1.0f, 0, 2.0f);
	// }
}

void UStageMonsterActorSpawnPoint::ActivateSpawnPoint(int32 StageLevel)
{
	// 레벨에 맞는 스폰 포인트 활성화
	bIsActive = true;
	UE_LOG(LogTemp, Log, TEXT("Spawn Point Activated for Stage Level %d"), StageLevel);

	// 레벨에 맞는 몬스터 스폰
	SpawnMonsters(StageLevel, nullptr);  // 데이터 테이블을 넘겨줄 필요 있음
}

void UStageMonsterActorSpawnPoint::DeactivateSpawnPoint()
{
	// 스폰 포인트 비활성화
	bIsActive = false;
	UE_LOG(LogTemp, Log, TEXT("Spawn Point Deactivated"));
}
