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

/*
 *	Meta Attributes
 */

	GameplayTags.Attributes_Meta_IncomingXP = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Meta.IncomingXP"),
		FString("Incoming XP Meta Attribute"));
	
	
/**
 *	Input Tags
 **/
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"),
		FString("InputTag for Left Mouse Button"));

	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("InputTag.RMB"),
	FString("InputTag for Right Mouse Button"));

	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("InputTag.1"),
	FString("InputTag for 1 key"));

	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("InputTag.2"),
	FString("InputTag for 2 key"));

	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("InputTag.3"),
	FString("InputTag for 3 key"));

	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("InputTag.4"),
	FString("InputTag for 4 key"));

	GameplayTags.InputTag_Passive_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("InputTag.Passive.1"),
	FString("InputTag for Passive 1"));

	GameplayTags.InputTag_Passive_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("InputTag.Passive.2"),
	FString("InputTag for Passive 2"));

/*
 * Damage Types
 */
	
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage"),
	FString("Generic Damage Type"));

	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage.Fire"),
	FString("Fire Damage Type"));

	GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage.Lightning"),
	FString("Lightning Damage Type"));
	
	GameplayTags.Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage.Arcane"),
	FString("Arcane Damage Type"));
	
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage.Physical"),
	FString("Physical Damage Type"));

/*
 * Resistances (resists)
 */
	GameplayTags.Attributes_Resist_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Resist.Fire"),
	FString("Fire Resistance Type"));
	
	GameplayTags.Attributes_Resist_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Resist.Lightning"),
	FString("Lightning Resistance Type"));
	
	GameplayTags.Attributes_Resist_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Resist.Arcane"),
	FString("Arcane Resistance Type"));
	
	GameplayTags.Attributes_Resist_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Resist.Physical"),
	FString("Physical Resistance Type"));
/*
 * Map Damage Types to Resists
 */
	GameplayTags.DamageTypesToResists.Add(GameplayTags.Damage_Fire, GameplayTags.Attributes_Resist_Fire);
	GameplayTags.DamageTypesToResists.Add(GameplayTags.Damage_Lightning, GameplayTags.Attributes_Resist_Lightning);
	GameplayTags.DamageTypesToResists.Add(GameplayTags.Damage_Arcane, GameplayTags.Attributes_Resist_Arcane);
	GameplayTags.DamageTypesToResists.Add(GameplayTags.Damage_Physical, GameplayTags.Attributes_Resist_Physical);

	
	
/*
 * Effects
 */
	
	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Effects.HitReact"),
	FString("Tag granted when hit reacting"));

/*
 * Abilities
 */
	
	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Attack"),
	FString("Attack Ability Tag"));

	GameplayTags.Abilities_Summon = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Summon"),
	FString("Summon Ability Tag"));

	GameplayTags.Abilities_Fire_Firebolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Fire.Firebolt"),
	FString("Firebolt Cooldown Tag"));

	GameplayTags.Abilities_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.HitReact"),
	FString("HitReact Ability Tag"));

	GameplayTags.Abilities_Status_Locked = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Status.Locked"),
	FString("Locked Status Tag"));
	
	GameplayTags.Abilities_Status_Eligible = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Status.Eligible"),
	FString("Eligible Status Tag"));

	GameplayTags.Abilities_Status_Unlocked = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Status.Unlocked"),
	FString("Unlocked Status Tag"));

	GameplayTags.Abilities_Status_Equipped = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Status.Equipped"),
	FString("Equipped Status Tag"));

	GameplayTags.Abilities_Type_Offensive = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Type.Offensive"),
	FString("Offensive Ability Type Tag"));
	
	GameplayTags.Abilities_Type_Defensive = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Type.Defensive"),
	FString("Defensive Ability Type Tag"));

	GameplayTags.Abilities_Type_Utility = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Type.Utility"),
	FString("Utility Ability Type Tag"));
	
	GameplayTags.Abilities_Type_Passive = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Type.Passive"),
	FString("Passive Ability Type Tag"));
	
	GameplayTags.Abilities_Type_None = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Type.None"),
	FString("Ability Type None Tag"));
	
	
	
	/*
	 *	Cooldowns
	 */
	
	GameplayTags.Cooldown_Fire_Firebolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Cooldown.Fire.Firebolt"),
	FString("Firebolt Ability Tag"));
	
/*
 * Montage
 */
	
	
	GameplayTags.Montage_Attack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Montage.Attack_1"),
	FString("Attack 1"));
	
	GameplayTags.Montage_Attack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Montage.Attack_2"),
	FString("Attack 2"));
	
	GameplayTags.Montage_Attack_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Montage.Attack_3"),
	FString("Attack 3"));

	GameplayTags.Montage_Attack_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Montage.Attack_4"),
	FString("Attack 4"));
	
	/*
	 * CombatSocket
	 */
	
	
	GameplayTags.CombatSocket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("CombatSocket.Weapon"),
	FString("Weapon Socket"));
	
	GameplayTags.CombatSocket_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("CombatSocket.RightHand"),
	FString("Right Hand Socket"));
	
	GameplayTags.CombatSocket_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("CombatSocket.LeftHand"),
	FString("Left Hand Socket"));

	GameplayTags.CombatSocket_Tail = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("CombatSocket.Tail"),
	FString("Tail Socket"));
	
}