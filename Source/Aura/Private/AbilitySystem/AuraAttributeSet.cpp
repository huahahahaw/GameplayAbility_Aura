// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAttributeSet.h"
#include <Net/UnrealNetwork.h>
#include "GameplayEffectExtension.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(25.f);
	InitMaxMana(50.f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}

}

void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& InProps)
{
	InProps.EffectContextHandle = Data.EffectSpec.GetContext();
	InProps.SourceASC = InProps.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	if (IsValid(InProps.SourceASC) && InProps.SourceASC->AbilityActorInfo.IsValid() && InProps.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		InProps.SourceAvatarActor = InProps.SourceASC->AbilityActorInfo->AvatarActor.Get();
		InProps.SourceController = InProps.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (InProps.SourceController == nullptr)
		{
			if (APawn* SourcePawn = Cast<APawn>(InProps.SourceAvatarActor))
			{
				InProps.SourceController = SourcePawn->GetController();
			}
		}
		if (InProps.SourceController)
		{
			ACharacter* SourcePawn = Cast<ACharacter>(InProps.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.Get())
	{
		InProps.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		InProps.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		InProps.TargetCharacter =Cast<ACharacter>(InProps.TargetAvatarActor);
		InProps.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InProps.TargetAvatarActor);
	}

}

void UAuraAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties EffectProperties;
	SetEffectProperties(Data, EffectProperties);

}

void UAuraAttributeSet::OnRep_Health(FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}
