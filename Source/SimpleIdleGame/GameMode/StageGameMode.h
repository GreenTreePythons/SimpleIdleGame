﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StageGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEIDLEGAME_API AStageGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AStageGameMode();

protected:
	virtual void BeginPlay() override;

private:
	void SpawnPlayerCharacter();
	void SetIngameWidget();
	void SetCamera();
};
