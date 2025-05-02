#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "StageMonsterActorSpawnPoint.h"
#include "StageManager.generated.h"

UCLASS(Blueprintable)  // 블루프린트에서 상속 가능하도록 설정
class SIMPLEIDLEGAME_API UStageManager : public UObject
{
	GENERATED_BODY()

public:
	UStageManager();

	// 현재 스테이지 레벨
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	int32 CurrentStageLevel;

	// 몬스터 스텟을 포함하는 데이터 테이블
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UDataTable* MonsterStatsTable;

	// 스폰 포인트 배열 (블루프린트에서 관리)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Points")
	TArray<UStageMonsterActorSpawnPoint*> SpawnPoints;

	// 스테이지 로드 시 세팅하는 함수
	UFUNCTION(BlueprintCallable, Category = "Stage")
	void SetupStage(int32 StageLevel);

	// 레벨에 맞는 스폰 포인트 처리
	void ActivateSpawnPointsForLevel(int32 StageLevel);
};
