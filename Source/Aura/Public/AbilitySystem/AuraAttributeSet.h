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
	 * Primary Attributes 力量、敏捷、智力
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Agile, Category = "Primary Attributes")
	FGameplayAttributeData Agile;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Agile);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intellect, Category = "Primary Attributes")
	FGameplayAttributeData Intellect;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intellect);

	/**
	 * Secondary Attributes
	 */
	//攻击速度
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackSpeed, Category = "Secondary Attributes")
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, AttackSpeed);
	//Armor护甲
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "Secondary Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance);

	//Critical暴击
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance);

	//生命恢复
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration);

	//魔法恢复
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Secondary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Secondary Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);
	/**
	 * Vital Attributes
	 */
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Health,Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);

	UFUNCTION()
	void OnRep_Strength(FGameplayAttributeData& OldStrength);

	UFUNCTION()
	void OnRep_Agile(FGameplayAttributeData& OldAgile);

	UFUNCTION()
	void OnRep_Intellect(FGameplayAttributeData& OldIntellect);

	UFUNCTION()
	void OnRep_AttackSpeed(FGameplayAttributeData& OldAttackSpeed);

	UFUNCTION()
	void OnRep_Armor(FGameplayAttributeData& OldArmor);

	UFUNCTION()
	void OnRep_ArmorPenetration(FGameplayAttributeData& OldArmorPenetration);

	UFUNCTION()
	void OnRep_BlockChance(FGameplayAttributeData& OldBlockChance);

	UFUNCTION()
	void OnRep_CriticalHitChance(FGameplayAttributeData& OldCriticalHitChance);

	UFUNCTION()
	void OnRep_CriticalHitDamage(FGameplayAttributeData& OldCriticalHitDamage);

	UFUNCTION()
	void OnRep_CriticalHitResistance(FGameplayAttributeData& OldCriticalHitResistance);

	UFUNCTION()
	void OnRep_HealthRegeneration(FGameplayAttributeData& OldHealthRegeneration);

	UFUNCTION()
	void OnRep_ManaRegeneration(FGameplayAttributeData& OldManaRegeneration);


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
