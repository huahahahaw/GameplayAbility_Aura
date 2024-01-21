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
	for (FGameplayTag Tag: GameplayTagContainer)
	{
		const FString Msg = FString::Printf(TEXT("GESpec GameTagName :%s"), *Tag.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Black, Msg);

	}

}
