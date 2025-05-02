// StageActorSpawnPoint.h
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StageMonsterActorSpawnPoint.generated.h"

// 몬스터 스폰 지점을 나타내는 UObject 클래스
UCLASS(Blueprintable)
class SIMPLEIDLEGAME_API UStageMonsterActorSpawnPoint : public UObject
{
	GENERATED_BODY()

public:
	UStageMonsterActorSpawnPoint();

	// 스폰할 몬스터의 종류
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Settings")
	TSubclassOf<class AMonsterActor> MonsterToSpawn;

	// 스폰할 몬스터의 레벨
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Settings")
	int32 MonsterLevel;

	// 스폰할 몬스터의 수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Settings")
	int32 SpawnCount;

	// 활성화 여부
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Settings")
	bool bIsActive;

	// 레벨에 맞는 몬스터 스폰 로직 처리
	void SpawnMonsters(int32 StageLevel, UDataTable* MonsterStatsTable);

	// 스폰 포인트 활성화/비활성화 처리
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void ActivateSpawnPoint(int32 StageLevel);  // 레벨을 인자로 받음

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void DeactivateSpawnPoint();
};
