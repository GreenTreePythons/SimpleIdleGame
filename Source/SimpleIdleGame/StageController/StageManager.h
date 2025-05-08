#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "StageInformation.h"
#include "StageMonsterActorSpawnPoint.h"  // 스폰 포인트 관련 클래스
#include "UObject/NoExportTypes.h"
#include "StageManager.generated.h"

// 스테이지 관리 클래스
UCLASS()
class SIMPLEIDLEGAME_API UStageManager : public UObject
{
	GENERATED_BODY()

public:
	UStageManager();

	// 스테이지 정보를 담고 있는 데이터 테이블
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage Info")
	UDataTable* StageDataTable;

	// 현재 스테이지 레벨
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage Info")
	int32 CurrentStageLevel;

	// 스폰 포인트 배열 (에디터에서 설정)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage Info")
	TArray<AStageMonsterActorSpawnPoint*> SpawnPoints;

	// 스테이지 세팅 함수
	void SetupStage(int32 StageLevel);

private:
	// 스테이지 레벨에 맞는 데이터를 불러오는 함수
	void LoadStageData(int32 StageLevel);

	// 몬스터 소환 함수
	void SpawnMonsters(const FString& MonsterName, int32 MonsterCount);

	// 스폰 포인트에서 몬스터 소환
	void SpawnMonstersAtSpawnPoint(int32 SpawnPointIndex, FStageInformation* StageInfo);

	// 몬스터 소환 함수
	void SpawnMonstersAtPoint(AStageMonsterActorSpawnPoint* SpawnPoint, const FString& MonsterName, int32 MonsterCount);
};
