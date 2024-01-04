// Copyright © 2023 Jodiah Jensen


#include "AbilitySystem/Data/LevelUpInfo.h"


int32 ULevelUpInfo::FindLevelForXP(int32 XP) const
{
	int32 Level =1;
	bool bSearching = true;
	while (bSearching)
	{
		//level up information at LevelUpInformation[1] = level 1 information, [2] is level 2 info etc
		if (LevelUpInformation.Num()-1 <= Level) return Level;

		if (XP >= LevelUpInformation[Level].LevelUpRequirement)
		{
			++Level;
		}
		else
		{
			bSearching = false;
		}
	}
	return Level;
}
