#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "StageMonsterActorSpawnPoint.h"
#include "MonsterActorInformation.h"
#include "StageManager.generated.h"

// 스테이지 관리 클래스
UCLASS()
class SIMPLEIDLEGAME_API UStageManager : public UObject
{
	GENERATED_BODY()

public:
	UStageManager();

	// 스테이지 레벨
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage Info")
	int32 CurrentStageLevel;

	// 몬스터 스텟을 담고 있는 데이터 테이블
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Stats")
	UDataTable* MonsterStatsTable;

	// 스폰 포인트 배열 (에디터에서 설정)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Points")
	TArray<AStageMonsterActorSpawnPoint*> SpawnPoints;

	// 스테이지 레벨에 맞게 스폰 포인트 활성화 및 몬스터 소환
	void SetupStage(int32 StageLevel);

private:
	// 스폰 포인트를 활성화하고 몬스터 소환
	void ActivateSpawnPointsForLevel(int32 StageLevel);
};
