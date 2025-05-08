// Fill out your copyright notice in the Description page of Project Settings.


#include "StageInformation.h"

FStageInformation::FStageInformation()
{
	StageLevel = 0;
	ActiveSpawnPointCount = 1;
	MonsterLevel1_Name = "MonsterLevel1";
	MonsterLevel1_Count = 0;
	MonsterLevel2_Name = "MonsterLevel2";
	MonsterLevel2_Count = 0;
	MonsterLevel3_Name = "MonsterLevel3";
	MonsterLevel3_Count = 0;
	ClearCondition = EStageClearCondition::None;
}
