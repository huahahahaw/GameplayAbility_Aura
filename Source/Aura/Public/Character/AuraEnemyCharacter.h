// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interfaction/EnemyInterface.h"
#include "Interfaction/CombatInterface.h"
#include "AuraEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemyCharacter : public AAuraCharacterBase,public IEnemyInterface,public ICombatInterface
{
	GENERATED_BODY()
public:
	AAuraEnemyCharacter();

	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

public:
	//IEnemyInterface
	virtual void HightLightActor() override;
	virtual void UnHightLightActor() override;

	//ICombatInterface
	int32 GetPlayerLevel() override;

protected:

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Character Class Defaults")
	int32 Level = 1;
};
