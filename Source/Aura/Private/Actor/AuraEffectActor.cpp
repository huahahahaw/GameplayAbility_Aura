// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("ScenceRootComponent"));

}


void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GamePlayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	check(GamePlayEffectClass);

	FGameplayEffectContextHandle GameplayEffectContextHandle = TargetASC->MakeEffectContext();
	GameplayEffectContextHandle.AddSourceObject(TargetActor);
	FGameplayEffectSpecHandle GameplayEffectSpec = TargetASC->MakeOutgoingSpec(GamePlayEffectClass, ActorLevel, GameplayEffectContextHandle);

	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpec.Data.Get());
	const bool bIsInfinite =GameplayEffectSpec.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite)
	{
		InfiniteActiveGameplayEffectHandles.Add(ActiveGameplayEffectHandle, TargetASC);
	}

}

void AAuraEffectActor::OnActorOverlap(AActor* TargetActor)
{
	if (InStantEffectApplicatiopnPolicy == EEffectApplicatiopnPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InStantGameplayEffectClass);
	}
	if (HasDurationEffectApplicatiopnPolicy == EEffectApplicatiopnPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, HasDurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicatiopnPolicy == EEffectApplicatiopnPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}


}

void AAuraEffectActor::OnActorEndOverlap(AActor* TargetActor)
{
	if (InStantEffectApplicatiopnPolicy == EEffectApplicatiopnPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InStantGameplayEffectClass);
	}
	if (HasDurationEffectApplicatiopnPolicy == EEffectApplicatiopnPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, HasDurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicatiopnPolicy == EEffectApplicatiopnPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}

	if (InfiniteEffectRemovalpolicy == EEffectRemovalpolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;

		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : InfiniteActiveGameplayEffectHandles)
		{
			if (HandlePair.Value == TargetASC)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key,1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}
		for (FActiveGameplayEffectHandle RemoveEffectHandle: HandlesToRemove)
		{
			InfiniteActiveGameplayEffectHandles.FindAndRemoveChecked(RemoveEffectHandle);
		}

	}

}

