// Copyright © 2023 Jodiah Jensen

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class ULevelUpInfo;
class UAbilitySystemComponent;
class UAttributeSet;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32 /*stat value*/)

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfo> LevelUpInfo;
	
	FOnPlayerStatChanged OnXPChangedDelegate;
	FOnPlayerStatChanged OnLevelChangedDelegate;
	
	FORCEINLINE int32 GetPlayerLevel() const { return PlayerLevel; }
	FORCEINLINE int32 GetXP() const { return XP; }

	void AddToXP(int32 InXP);
	void AddToPlayerLevel(int32 InLevel);
	
	void SetXP(int32 InXP);
	void SetPlayerLevel(int32 InLevel);
	
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;


private:
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_PlayerLevel)
	int32 PlayerLevel = 1;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_XP)
	int32 XP = 1;
	
	UFUNCTION()
	void OnRep_PlayerLevel(int32 OldLevel);

	UFUNCTION()
	void OnRep_XP(int32 OldXP);
};
