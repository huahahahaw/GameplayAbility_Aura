// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Hud/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(FWidgetControllerParams& WCP)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCP);

		return OverlayWidgetController;
	}
	
	return OverlayWidgetController;
}



void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class UnInitialized,Please fill out BP_AuraHud"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class UnInitialized,Please fill out BP_AuraHud"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass, FName("OverlayWidget"));
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
	UOverlayWidgetController* InOverlayWidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(InOverlayWidgetController);

	Widget->AddToViewport();
}

