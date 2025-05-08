// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "StageInformation.generated.h"

UENUM(BlueprintType)
enum class EStageClearCondition : uint8
{
	AllMonstersDead UMETA(DisplayName = "All Monsters Dead"),
	TimeLimit UMETA(DisplayName = "Time Limit"),
	SpecificObjective UMETA(DisplayName = "Specific Objective"),
	None UMETA(DisplayName = "None")  // 기본값
};

USTRUCT(BlueprintType)
struct FStageInformation : public FTableRowBase
{
	GENERATED_BODY()

public:
	FStageInformation();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
	int32 StageLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
	int32 ActiveSpawnPointCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
	FString MonsterLevel1_Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
	int32 MonsterLevel1_Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
	FString MonsterLevel2_Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
	int32 MonsterLevel2_Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
	FString MonsterLevel3_Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
	int32 MonsterLevel3_Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
	EStageClearCondition ClearCondition;
};
