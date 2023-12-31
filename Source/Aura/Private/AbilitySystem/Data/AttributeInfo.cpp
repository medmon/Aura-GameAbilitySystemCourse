// Copyright © 2023 Jodiah Jensen


#include "AbilitySystem/Data/AttributeInfo.h"

#include "Aura/AuraLogChannels.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for(const FAuraAttributeInfo& Info : AttributeInfo)
	{
		if(Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogAura, Error, TEXT("Can't find info for AttributeTag [%s] on AttributeInfo [%s]."),
			*AttributeTag.ToString(),
			*GetNameSafe(this)
			);
	}

	return FAuraAttributeInfo();
}
