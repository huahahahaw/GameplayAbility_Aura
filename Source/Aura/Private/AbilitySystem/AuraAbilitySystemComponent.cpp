// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include <AuraGameplayTags.h>

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);

	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Tag : %s"), *GameplayTags.Attributes_Secondary_Armor.ToString()));
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* InASC, const FGameplayEffectSpec& InGESpec, FActiveGameplayEffectHandle InActiveGEHandle)
{
	FGameplayTagContainer GameplayTagContainer;
	InGESpec.GetAllAssetTags(GameplayTagContainer);
	EffectAssertTagsDelegate.Broadcast(GameplayTagContainer);
}
