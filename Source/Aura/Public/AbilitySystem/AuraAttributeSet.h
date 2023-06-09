// Copyright © 2023 Jodiah Jensen

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

/**
 * This defines a set of helper functions for accessing and initializing attributes, to avoid having to manually write these functions.
 * It would creates the following functions, for attribute Health
 *
 *	static FGameplayAttribute UMyHealthSet::GetHealthAttribute();
 *	FORCEINLINE float UMyHealthSet::GetHealth() const;
 *	FORCEINLINE void UMyHealthSet::SetHealth(float NewVal);
 *	FORCEINLINE void UMyHealthSet::InitHealth(float NewVal);
 *
 * To use this in your game you can define something like this, and then add game-specific functions as necessary:
 * 
 *	#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 *	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 *	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 *	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 *	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
 * 
 *	ATTRIBUTE_ACCESSORS(UMyHealthSet, Health)
 */
	#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)



USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;
//source
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;
	
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

//target
	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;
	
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;


	
};

// this typedef is specific to the FGameplayAttribute() signature
//typedef TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;

template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAuraAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;


	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;

/*
 *	Primary Attributes
 */

//Strength
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, category = "Primary Atrributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData OldStrength) const;

//Intelligence
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, category = "Primary Atrributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData OldIntelligence) const;

//Resilience
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, category = "Primary Atrributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);

	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData OldResilience) const;

//Vigor	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, category = "Primary Atrributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData OldVigor) const;

/*
 *	Secondary Attributes
 */
//Armor
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, category = "Secondary Atrributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData OldArmor) const;

//Armor Penetration
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPen, category = "Secondary Atrributes")
	FGameplayAttributeData ArmorPen;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPen);

	UFUNCTION()
	void OnRep_ArmorPen(const FGameplayAttributeData OldArmorPen) const;

//Block Chance
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Block, category = "Secondary Atrributes")
	FGameplayAttributeData Block;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Block);

	UFUNCTION()
	void OnRep_Block(const FGameplayAttributeData OldBlock) const;

//Crit Hit Chance
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritHit, category = "Secondary Atrributes")
	FGameplayAttributeData CritHit;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CritHit);

	UFUNCTION()
	void OnRep_CritHit(const FGameplayAttributeData OldCritHit) const;

//Crit Hit Bonus
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritDmg, category = "Secondary Atrributes")
	FGameplayAttributeData CritDmg;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CritDmg);

	UFUNCTION()
	void OnRep_CritDmg(const FGameplayAttributeData OldCritDmg) const;

//Crit Resistance
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritResist, category = "Secondary Atrributes")
	FGameplayAttributeData CritResist;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CritResist);

	UFUNCTION()
	void OnRep_CritResist(const FGameplayAttributeData OldCritResist) const;

//Health Regen
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegen, category = "Secondary Atrributes")
	FGameplayAttributeData HealthRegen;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegen);

	UFUNCTION()
	void OnRep_HealthRegen(const FGameplayAttributeData OldHealthRegen) const;

//Mana Regen
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegen, category = "Secondary Atrributes")
	FGameplayAttributeData ManaRegen;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegen);

	UFUNCTION()
	void OnRep_ManaRegen(const FGameplayAttributeData OldManaRegen) const;

	

/*
 *	Vital Attributes
 */
		
//Health
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, category = "Vital Atrributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, category = "Vital Atrributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData OldHealth) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData OldMaxMana) const;

//Mana
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, category = "Vital Atrributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, category = "Vital Atrributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData OldMana) const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData OldMaxMana) const;

private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
