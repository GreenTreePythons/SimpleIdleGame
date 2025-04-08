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
    // UMG 위젯 클래스
    UPROPERTY()
    TSubclassOf<class UUserWidget> TitleWidgetClass;

    // 생성된 위젯 인스턴스
    UPROPERTY()
    class UUserWidget* TitleWidget;
};