#include "TitleHUD.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

void ATitleHUD::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("[TitleHUD] BeginPlay called"));
    
    TitleWidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Widgets/WBP_TitleWidget.WBP_TitleWidget_C"));
    
    if (TitleWidgetClass)
    {
        TitleWidget = CreateWidget<UUserWidget>(GetWorld(), TitleWidgetClass);
        if (TitleWidget)
        {
            TitleWidget->AddToViewport();
        }
    }
}