// Copyright © 2023 Jodiah Jensen


#include "AuraGameplayTags.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
/**
 *	Primary Attributes
 **/
	
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"),
		FString("Increases physical damage"));

	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"),
		FString("Increases magical damage"));

	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Resilience"),
		FString("Increases Armor and Armor Penetration"));

	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Vigor"),
		FString("Increases Health"));

/**
 *	Secondary Attributes
 **/
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"),
		FString("Reduces damage taken, improves block chance"));

	GameplayTags.Attributes_Secondary_ArmorPen = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorPen"),
		FString("Ignore percentage of enemy armor, Increases Crit Hit Chance"));

	GameplayTags.Attributes_Secondary_Block = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Block"),
		FString("Chance to cut incoming damage by half"));

	GameplayTags.Attributes_Secondary_CritHit = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CritHit"),
		FString("Chance to double damage plus critical damage bonus"));

	GameplayTags.Attributes_Secondary_CritDmg = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CritDmg"),
		FString("Bonus damage when crit hit is scored"));

	GameplayTags.Attributes_Secondary_CritResist = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CritResist"),
		FString("Reduces crit hit chance of attacking enemies"));

	GameplayTags.Attributes_Secondary_HealthRegen = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.HealthRegen"),
		FString("Health regenerated per 1 second"));

	GameplayTags.Attributes_Secondary_ManaRegen = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ManaRegen"),
		FString("Mana regenerated per 1 second"));

	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"),
		FString("Maximum Health Attainable"));

	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"),
		FString("Maximum Mana Attainable"));
    

	
}