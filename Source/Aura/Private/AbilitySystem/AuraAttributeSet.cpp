// Copyright © 2023 Jodiah Jensen


#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"


UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(1000.f);
	InitMaxMana(1000.f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//register for replication

	//health
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Health,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth,COND_None, REPNOTIFY_Always);
	//mana
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Mana,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana,COND_None, REPNOTIFY_Always);
	
}

//health
void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData OldHealth) const
{
	//inform the Ability System that an attribute has been replicated
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}
void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData OldMaxHealth) const
{
	//inform the Ability System that an attribute has been replicated
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

//mana
void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData OldMana) const
{
	//inform the Ability System that an attribute has been replicated
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData OldMaxMana) const
{
	//inform the Ability System that an attribute has been replicated
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Mana, OldMaxMana);
}
