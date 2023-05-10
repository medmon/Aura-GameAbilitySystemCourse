// Copyright © 2023 Jodiah Jensen

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

/** Combat Interface */
		virtual int32 GetCharLevel() override;
/** End Combat Interface */
private:
	virtual void InitAbilityActorInfo() override;
};
