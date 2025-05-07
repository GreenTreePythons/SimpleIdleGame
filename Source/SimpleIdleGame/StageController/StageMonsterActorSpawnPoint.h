// StageMonsterActorSpawnPoint.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterActor.h"
#include "StageMonsterActorSpawnPoint.generated.h"

// 스폰 포인트에서 몬스터를 소환하는 클래스
UCLASS()
class SIMPLEIDLEGAME_API AStageMonsterActorSpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	// 기본 생성자
	AStageMonsterActorSpawnPoint();

	// 레벨에 맞는 스폰 몬스터 정보
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Info")
	TSubclassOf<AMonsterActor> MonsterToSpawn;

	// 몬스터의 스폰 수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Info")
	int32 SpawnCount;

	// 몬스터 스텟 데이터 테이블
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Info")
	UDataTable* MonsterStatsTable;

	// 몬스터를 스폰하는 함수
	void SpawnMonsters(int32 StageLevel);

	// 스폰 포인트를 활성화
	void ActivateSpawnPoint(int32 StageLevel);

	// 비활성화 메소드
	void DeactivateSpawnPoint();
};
