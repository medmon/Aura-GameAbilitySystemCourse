// Copyright © 2023 Jodiah Jensen


#include "AbilitySystem/Abilities/AuraFirebolt.h"

#include "AuraGameplayTags.h"

FString UAuraFirebolt::GetDescription(int32 Level)
{
	const int32 Damage = DamageTypes[FAuraGameplayTags::Get().Damage_Fire].GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	
	if (Level == 1)
	{
		return FString::Printf(
			TEXT("<Title>FIRE BOLT</>\n\n"
				"<Small>Level: </><Level>%d</>\n"
				"<Small>Mana Cost: </><ManaCost>%.1f</>\n"
				"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
				"<Default> Launches a bolt of fire, "
				"exploding on impact and dealing </>"
				"<Damage>%d</>"
				"<Default> fire damage with a chance to burn</>\n\n"),
							Level, ManaCost, Cooldown, Damage
			);
	}
	else
	{
		return FString::Printf(
			TEXT("<Title>FIRE BOLT</>\n\n"
				"<Small>Level: </><Level>%d</>\n"
				"<Small>Mana Cost</><ManaCost>%.1f</>\n"
				"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
				"<Default> Launches %d bolts of fire, "
				"exploding on impact and dealing </>"
				"<Damage>%d</>"
				"<Default> fire damage with a chance to burn</>\n\n"),
							Level, ManaCost, Cooldown, FMath::Min(Level, NumProjectiles), Damage
			);
	
	}

	return FString::Printf(TEXT(""));
}

FString UAuraFirebolt::GetNextLevelDescription(int32 Level)
{
	const int32 Damage = DamageTypes[FAuraGameplayTags::Get().Damage_Fire].GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);

	return FString::Printf(
		TEXT("<Title>NEXT LEVEL</>\n\n"
			"<Small>Level: </><Level>%d</>\n"
			"<Small>Mana Cost</><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			"<Default> Launches %d bolts of fire, "
			"exploding on impact and dealing </>"
			"<Damage>%d</>"
			"<Default> fire damage with a chance to burn</>\n\n"),
						Level, ManaCost, Cooldown, FMath::Min(Level, NumProjectiles), Damage
		);

}
