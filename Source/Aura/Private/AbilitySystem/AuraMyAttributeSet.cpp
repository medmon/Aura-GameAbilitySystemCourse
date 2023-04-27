// Copyright © 2023 Jodiah Jensen


#include "AbilitySystem/AuraMyAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"


UAuraMyAttributeSet::UAuraMyAttributeSet()
{
	
}

void UAuraMyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//register for replication

	//health
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraMyAttributeSet,Health,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraMyAttributeSet, MaxHealth,COND_None, REPNOTIFY_Always);
	//mana
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraMyAttributeSet,Mana,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraMyAttributeSet, MaxMana,COND_None, REPNOTIFY_Always);
	
}

//health
void UAuraMyAttributeSet::OnRep_Health(const FGameplayAttributeData OldHealth) const
{
	//inform the Ability System that an attribute has been replicated
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraMyAttributeSet, Health, OldHealth);
}
void UAuraMyAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData OldMaxHealth) const
{
	//inform the Ability System that an attribute has been replicated
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraMyAttributeSet, MaxHealth, OldMaxHealth);
}

//mana
void UAuraMyAttributeSet::OnRep_Mana(const FGameplayAttributeData OldMana) const
{
	//inform the Ability System that an attribute has been replicated
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraMyAttributeSet, Mana, OldMana);
}

void UAuraMyAttributeSet::OnRep_MaxMana(const FGameplayAttributeData OldMaxMana) const
{
	//inform the Ability System that an attribute has been replicated
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraMyAttributeSet,Mana, OldMaxMana);
}
