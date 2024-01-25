// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

struct FGameplayEffectContextHandle;
class UAbilitySystemComponent;
struct FGameplayEffectContextHandle;


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
USTRUCT(BlueprintType)
struct FEffectProperties
{
	GENERATED_BODY()
	FEffectProperties(){ }

	FGameplayEffectContextHandle EffectContextHandle;

	//Source
	UPROPERTY()
		TObjectPtr<UAbilitySystemComponent> SourceASC;

	UPROPERTY()
		TObjectPtr<AActor> SourceAvatarActor;

	UPROPERTY()
		TObjectPtr<AController> SourceController;

	UPROPERTY()
		TObjectPtr<ACharacter> SourceCharacter;

	//Target
	UPROPERTY()
		TObjectPtr<UAbilitySystemComponent> TargetASC;

	UPROPERTY()
		TObjectPtr<AActor> TargetAvatarActor;

	UPROPERTY()
		TObjectPtr<AController> TargetController;

	UPROPERTY()
		TObjectPtr<ACharacter> TargetCharacter;

};


UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	/**
	 * Primary Attributes
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "Primary Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);

	/**
	 * Vital Attributes
	 */
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Health,Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);


	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);

	UFUNCTION()
	void OnRep_Strength(FGameplayAttributeData& OldStrength);

	UFUNCTION()
	void OnRep_Intelligence(FGameplayAttributeData& OldIntelligence);

	UFUNCTION()
	void OnRep_Resilience(FGameplayAttributeData& OldResilience);

	UFUNCTION()
	void OnRep_Vigor(FGameplayAttributeData& OldVigor);


	UFUNCTION()
	void OnRep_Health(FGameplayAttributeData& OldHealth);
	UFUNCTION()
	void OnRep_MaxHealth(FGameplayAttributeData& OldMaxHealth);
	UFUNCTION()
	void OnRep_Mana(FGameplayAttributeData& OldMana);
	UFUNCTION()
	void OnRep_MaxMana(FGameplayAttributeData& OldMaxMana);
private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& InProps);
};
