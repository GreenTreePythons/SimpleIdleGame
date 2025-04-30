#include "TitleHUD.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

void ATitleHUD::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("[TitleHUD] BeginPlay called"));
    
    TitleWidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Widgets/WBP_TitleWidget.WBP_TitleWidget_C"));
    
    if (!TitleWidgetClass) return;
    
    TitleWidget = CreateWidget<UUserWidget>(GetWorld(), TitleWidgetClass);
    if (!TitleWidget) return;
    
    TitleWidget->AddToViewport();
}