// MonsterActor.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterActorInformation.h"
#include "MonsterActor.generated.h"

UCLASS()
class SIMPLEIDLEGAME_API AMonsterActor : public AActor
{
	GENERATED_BODY()

public:
	AMonsterActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// 몬스터의 다양한 정보
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Info")
	FMonsterActorInformation MonsterInformation;

	// 몬스터 공격 방법 (근접 또는 원거리)
	void Attack();

	// 몬스터 타입에 따른 공격 함수
	void MeleeAttack();
	void RangedAttack();
};
