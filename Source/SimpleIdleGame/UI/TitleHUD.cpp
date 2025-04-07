#include "TitleHUD.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

ATitleHUD::ATitleHUD()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> TitleWidgetBP(TEXT("/Game/BluePrints/WBP_TitleWidget.WBP_TitleWidget_C"));
    if (TitleWidgetBP.Succeeded())
    {
        TitleWidgetClass = TitleWidgetBP.Class;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("[TitleHUD] Failed to find WBP_TitleWidget at path: /Game/BluePrints/WBP_TitleWidget"));
    }
}

void ATitleHUD::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("[TitleHUD] BeginPlay() called"));

    if (TitleWidgetClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("[TitleHUD] TitleWidgetClass is valid"));

        TitleWidget = CreateWidget<UUserWidget>(GetWorld(), TitleWidgetClass);
        if (TitleWidget)
        {
            UE_LOG(LogTemp, Warning, TEXT("[TitleHUD] Widget created successfully"));
            TitleWidget->AddToViewport(100);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("[TitleHUD] CreateWidget failed"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("[TitleHUD] TitleWidgetClass is null"));
    }
}