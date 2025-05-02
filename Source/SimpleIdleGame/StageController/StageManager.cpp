#include "StageManager.h"
#include "MonsterActorInformation.h"
#include "StageMonsterActorSpawnPoint.h"
#include "Engine/World.h"
#include "Engine/DataTable.h"

UStageManager::UStageManager()
{
	// 기본 스테이지 레벨 설정 (예: 1부터 시작)
	CurrentStageLevel = 1;
}

void UStageManager::SetupStage(int32 StageLevel)
{
	CurrentStageLevel = StageLevel;
	ActivateSpawnPointsForLevel(CurrentStageLevel);
}

void UStageManager::ActivateSpawnPointsForLevel(int32 StageLevel)
{
	// StageLevel에 맞는 스폰 포인트 활성화/비활성화 처리
	for (UStageMonsterActorSpawnPoint* SpawnPoint : SpawnPoints)
	{
		if (SpawnPoint)
		{
			// 데이터 테이블에서 몬스터 스텟을 찾아오기
			static const FString ContextString(TEXT("Stage Level Spawn Info Context"));
			FMonsterActorInformation* LevelSpawnInfo = MonsterStatsTable->FindRow<FMonsterActorInformation>(FName(*FString::FromInt(StageLevel)), ContextString);
            
			if (LevelSpawnInfo)
			{
				// 몬스터 스텟에 맞는 스폰 포인트 활성화
				SpawnPoint->ActivateSpawnPoint(StageLevel);
			}
		}
	}
}
