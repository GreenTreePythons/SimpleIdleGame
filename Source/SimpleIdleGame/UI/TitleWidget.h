#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidget.generated.h"

UCLASS()
class SIMPLEIDLEGAME_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnClickSinglePlay();

	UFUNCTION()
	void OnClickMultiPlay();

	UFUNCTION()
	void OnClickExit();

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_SinglePlay;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_MultiPlay;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Exit;
};