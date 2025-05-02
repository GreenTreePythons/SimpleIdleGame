#pragma once

#include "CoreMinimal.h"
#include "EditorMetadataOverrides.h"
#include "Engine/DataTable.h"
#include "MonsterActorInformation.generated.h"

// 몬스터의 다양한 정보를 관리하는 구조체
USTRUCT(BlueprintType)
struct FMonsterActorInformation : public FTableRowBase
{
	GENERATED_BODY()

public:
	FMonsterActorInformation()
		: Name("default"), Rank(1), Level(1), Health(100.0f), AttackPower(10.0f), DefensePower(5.0f),  AttackRange(1.0f)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
	FString Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
	int32 Rank;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float AttackPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float DefensePower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float AttackRange;
};
