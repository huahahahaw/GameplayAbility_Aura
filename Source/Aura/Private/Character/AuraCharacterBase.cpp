// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacterBase.h"
#include "AbilitySystemComponent.h"


// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraCharacterBase::ApplyEffectToTarget(TSubclassOf<UGameplayEffect> InEffect, int Inlevel)
{
	check(IsValid(GetAbilitySystemComponent()));
	check(InEffect);

	FGameplayEffectContextHandle EffectContext = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle GESpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(InEffect, Inlevel, EffectContext);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*GESpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AAuraCharacterBase::InitDefaultAttribute()
{
	ApplyEffectToTarget(PrimaryEffect, 1.f);
	ApplyEffectToTarget(SecondaryEffect, 1.f);
}

void AAuraCharacterBase::InitAbilityActorInfo()
{

}
