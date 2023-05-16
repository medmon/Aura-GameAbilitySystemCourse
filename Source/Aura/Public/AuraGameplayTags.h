// Copyright © 2023 Jodiah Jensen

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"


/**
 *	AuraGameplayTags
 *
 *	Singleton containing native gameplay tags
 */
struct FAuraGameplayTags
{
public:
 static const FAuraGameplayTags& Get() { return GameplayTags; }
 static void InitializeNativeGameplayTags()
 {
   UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"),
   	FString("Reduces damage taken, improves block chance"));
 	
 }
protected:

private:
	static FAuraGameplayTags GameplayTags;
};
