// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Hud/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	UAuraUserWidget* Widget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayWidgetClass, FName("OverlayWidget"));
	Widget->AddToViewport();

}
