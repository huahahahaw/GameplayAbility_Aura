// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "MenuAttributeWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMenuAttributeWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BoradcastInitialValues() override;

	virtual void BindCallbacksToDependencies() override;

};
