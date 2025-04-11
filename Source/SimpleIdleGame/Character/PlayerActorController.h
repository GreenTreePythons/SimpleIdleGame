// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerActorController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEIDLEGAME_API APlayerActorController : public APlayerController
{
	GENERATED_BODY()

public:
	APlayerActorController();

protected:
	virtual void SetupInputComponent() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
};
