// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "GameplayEffectTypes.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BoradcastInitialValues() override;

	virtual void BindCallbacksToDependencies() override;
	
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attribute")
	FOnHealthChangedSignature OnHealthChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")
	FOnMaxHealthChangedSignature OnMaxHealthChangedDelegate;
public:
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
};
