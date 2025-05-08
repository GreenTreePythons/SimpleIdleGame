#include "StageManager.h"
#include "StageMonsterActorSpawnPoint.h"
#include "MonsterActor.h"  // 몬스터 클래스
#include "Engine/World.h"

UStageManager::UStageManager()
{
    CurrentStageLevel = 1;  // 기본값
}

void UStageManager::SetupStage(int32 StageLevel)
{
    CurrentStageLevel = StageLevel;
    LoadStageData(CurrentStageLevel);
}

void UStageManager::LoadStageData(int32 StageLevel)
{
    if (StageDataTable)
    {
        // 데이터 테이블에서 해당 레벨의 스테이지 정보를 찾는다
        static const FString ContextString(TEXT("Stage Info Context"));
        FStageInformation* StageInfo = StageDataTable->FindRow<FStageInformation>(FName(*FString::FromInt(StageLevel)), ContextString);

        if (StageInfo)
        {
            UE_LOG(LogTemp, Log, TEXT("Stage Level: %d"), StageInfo->StageLevel);
            UE_LOG(LogTemp, Log, TEXT("Spawn Point Count: %d"), StageInfo->ActiveSpawnPointCount);

            // 몬스터 소환 (스테이지 레벨에 맞는 몬스터 이름과 갯수)
            if (!StageInfo->MonsterLevel1_Name.IsEmpty())
            {
                SpawnMonsters(StageInfo->MonsterLevel1_Name, StageInfo->MonsterLevel1_Count);
            }
            if (!StageInfo->MonsterLevel2_Name.IsEmpty())
            {
                SpawnMonsters(StageInfo->MonsterLevel2_Name, StageInfo->MonsterLevel2_Count);
            }
            if (!StageInfo->MonsterLevel3_Name.IsEmpty())
            {
                SpawnMonsters(StageInfo->MonsterLevel3_Name, StageInfo->MonsterLevel3_Count);
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Stage Level %d data not found"), StageLevel);
        }
    }
}


// 몬스터 소환 함수
void UStageManager::SpawnMonsters(const FString& MonsterName, int32 MonsterCount)
{
    for (int32 i = 0; i < MonsterCount; ++i)
    {
        FActorSpawnParameters SpawnParams;
        GetWorld()->SpawnActor<AMonsterActor>(AMonsterActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
        UE_LOG(LogTemp, Log, TEXT("Spawned %s"), *MonsterName);
    }
}

// 스폰 포인트에서 몬스터 소환
void UStageManager::SpawnMonstersAtSpawnPoint(int32 SpawnPointIndex, FStageInformation* StageInfo)
{
    if (SpawnPoints.IsValidIndex(SpawnPointIndex))
    {
        AStageMonsterActorSpawnPoint* SpawnPoint = SpawnPoints[SpawnPointIndex];
        if (SpawnPoint)
        {
            // 몬스터 소환
            SpawnMonstersAtPoint(SpawnPoint, StageInfo->MonsterLevel1_Name, StageInfo->MonsterLevel1_Count);
            SpawnMonstersAtPoint(SpawnPoint, StageInfo->MonsterLevel2_Name, StageInfo->MonsterLevel2_Count);
            SpawnMonstersAtPoint(SpawnPoint, StageInfo->MonsterLevel3_Name, StageInfo->MonsterLevel3_Count);
        }
    }
}

// 개별 스폰 포인트에서 몬스터 소환
void UStageManager::SpawnMonstersAtPoint(AStageMonsterActorSpawnPoint* SpawnPoint, const FString& MonsterName, int32 MonsterCount)
{
    if (MonsterCount > 0)
    {
        for (int32 i = 0; i < MonsterCount; ++i)
        {
            // 실제로 몬스터를 스폰할 때는 몬스터 클래스와 위치를 고려하여 소환해야 합니다.
            GetWorld()->SpawnActor<AMonsterActor>(AMonsterActor::StaticClass(), SpawnPoint->GetActorLocation(), SpawnPoint->GetActorRotation());
            UE_LOG(LogTemp, Log, TEXT("Spawned %d %s at spawn point"), MonsterCount, *MonsterName);
        }
    }
}
