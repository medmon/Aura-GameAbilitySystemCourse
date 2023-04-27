// Copyright © 2023 Jodiah Jensen

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AuraMyAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraMyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAuraMyAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

//health
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, category = "Vital Atrributes")
	FGameplayAttributeData Health;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, category = "Vital Atrributes")
	FGameplayAttributeData MaxHealth;

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData OldHealth) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData OldMaxMana) const;

//mana
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, category = "Vital Atrributes")
	FGameplayAttributeData Mana;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, category = "Vital Atrributes")
	FGameplayAttributeData MaxMana;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData OldMana) const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData OldMaxMana) const;

	
};
