// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActiveGameplayEffectHandle.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;

UENUM(BlueprintType)
enum class EEffectApplicatiopnPolicy
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};
UENUM(BlueprintType)
enum class EEffectRemovalpolicy
{
	RemoveOnEndOverlap,
	DoNotRemove
};



UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAuraEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GamePlayEffectClass);

	UFUNCTION(BlueprintCallable)
	void OnActorOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnActorEndOverlap(AActor* TargetActor);

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> InfiniteActiveGameplayEffectHandles;

	//InStant
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Applied Effects|InStant")
	TSubclassOf<UGameplayEffect> InStantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects|InStant")
	EEffectApplicatiopnPolicy InStantEffectApplicatiopnPolicy = EEffectApplicatiopnPolicy::DoNotApply;

	//HasDuration
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects|HasDuration")
	TSubclassOf<UGameplayEffect> HasDurationGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects|HasDuration")
	EEffectApplicatiopnPolicy HasDurationEffectApplicatiopnPolicy = EEffectApplicatiopnPolicy::DoNotApply;


	//Infinite
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects|Infinite")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects|Infinite")
	EEffectApplicatiopnPolicy InfiniteEffectApplicatiopnPolicy = EEffectApplicatiopnPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects|Infinite")
	EEffectRemovalpolicy InfiniteEffectRemovalpolicy = EEffectRemovalpolicy::DoNotRemove;

};
