// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* InASC, const FGameplayEffectSpec& InGESpec, FActiveGameplayEffectHandle InActiveGEHandle)
{
	FGameplayTagContainer GameplayTagContainer;
	InGESpec.GetAllAssetTags(GameplayTagContainer);
	EffectAssertTagsDelegate.Broadcast(GameplayTagContainer);
}
