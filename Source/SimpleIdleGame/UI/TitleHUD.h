#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TitleHUD.generated.h"

UCLASS()
class SIMPLEIDLEGAME_API ATitleHUD : public AHUD
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

private:
    ATitleHUD();
    
    TSubclassOf<class UUserWidget> TitleWidgetClass;
    class UUserWidget* TitleWidget;
};