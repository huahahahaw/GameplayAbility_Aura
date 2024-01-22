// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"
#include <AbilitySystem/AuraAttributeSet.h>
#include <AbilitySystem/AuraAbilitySystemComponent.h>

void UOverlayWidgetController::BoradcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);	
	OnHealthChangedDelegate.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChangedDelegate.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChangedDelegate.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChangedDelegate.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	//Health
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda
	(
		[this](const FOnAttributeChangeData& Data) {
			OnHealthChangedDelegate.Broadcast(Data.NewValue);
		}
	);
	//MaxHealth
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda
	(
		[this](const FOnAttributeChangeData& Data) {
			OnMaxHealthChangedDelegate.Broadcast(Data.NewValue);
		}
	);
	//Mana
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda
	(
		[this](const FOnAttributeChangeData& Data) {
			OnManaChangedDelegate.Broadcast(Data.NewValue);
		}
	);
	//MaxMana
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda
	(
		[this](const FOnAttributeChangeData& Data) {
			OnMaxManaChangedDelegate.Broadcast(Data.NewValue);
		}
	);

	//Tag Messages
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssertTagsDelegate.AddLambda(
		[this](const FGameplayTagContainer& TagContainer)
		{
			FGameplayTag MatchTag = FGameplayTag::RequestGameplayTag("Messages");
			for (FGameplayTag Tag : TagContainer)
			{
				if (Tag.MatchesTag(MatchTag))
				{
					FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDT, Tag);
					OnUIWidgetMessageDelegate.Broadcast(*Row);
				}
			}
		}
	);
}
