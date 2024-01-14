// Copyright © 2023 Jodiah Jensen


#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Aura/AuraLogChannels.h"
#include "Interaction/CombatInterface.h"
#include "Interaction/PlayerInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/AuraPlayerController.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
//primary attributes
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Strength, GetStrengthAttribute);

	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Intelligence, GetIntelligenceAttribute);

	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Resilience, GetResilienceAttribute);

	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Vigor, GetVigorAttribute);

//secondary attributes
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Armor, GetArmorAttribute);

	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ArmorPen, GetArmorPenAttribute);

	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Block, GetBlockAttribute);

	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CritHit, GetCritHitAttribute);

	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CritDmg, GetCritDmgAttribute);

	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CritResist, GetCritResistAttribute);

	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_HealthRegen, GetHealthRegenAttribute);

	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ManaRegen, GetManaRegenAttribute);

	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxHealth, GetMaxHealthAttribute);

	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxMana, GetMaxManaAttribute);

	//resistance attributes
	TagsToAttributes.Add(GameplayTags.Attributes_Resist_Fire, GetFireResistAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resist_Lightning, GetLightningResistAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resist_Arcane, GetArcaneResistAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resist_Physical, GetPhysicalResistAttribute);
	
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	/*
	 *	register for replication
	 */
	//Primary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Strength,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Intelligence,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Resilience,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Vigor,COND_None, REPNOTIFY_Always);

	//Secondary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Armor,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,ArmorPen,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Block,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,CritHit,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,CritDmg,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,CritResist,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,HealthRegen,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,ManaRegen,COND_None, REPNOTIFY_Always);

	//Resistance Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,FireResist,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,LightningResist,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,ArcaneResist,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,PhysicalResist,COND_None, REPNOTIFY_Always);

	
	//health
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Health,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth,COND_None, REPNOTIFY_Always);
	//mana
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Mana,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana,COND_None, REPNOTIFY_Always);
	
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	
	}
	
}

void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	//source - causer of the effect, Target = target of the effect(Owner of this AS)
	
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if(IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if(Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if(Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
		
	}

}


void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
//DBG                                                                                                                                                                                                                 		UE_LOG(LogTemp, Warning, TEXT("Changed Health on %s, Health: %f"), *Props.TargetAvatarActor->GetName(), GetHealth())
	}
	if(Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
	if(Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0.f);
		if(LocalIncomingDamage > 0.f)
		{
			const float NewHealth = GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));

			const bool bFatal = NewHealth <= 0.f;
			if (bFatal)
			{
				ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetAvatarActor);
				if(CombatInterface)
				{
					CombatInterface->Die();
				}
				SendXPEvent(Props);
			}
			else
			{
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(FAuraGameplayTags::Get().Effects_HitReact);
				Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
			}

			const bool bBlock = UAuraAbilitySystemLibrary::IsBlockedHit(Props.EffectContextHandle);
			const bool bCrit = UAuraAbilitySystemLibrary::IsCriticalHit(Props.EffectContextHandle);
			
			ShowFloatingText(Props, LocalIncomingDamage, bBlock, bCrit);

		}
		
	}
	
	if(Data.EvaluatedData.Attribute == GetIncomingXPAttribute())
	{
		const float LocalIncomingXP = GetIncomingXP();
		SetIncomingXP(0.f);
		
		UE_LOG(LogAura, Log, TEXT("Incoming XP: %f"), LocalIncomingXP);

		// Source Character is the owner, since GA_ListenForEvents applies GE_EventBasedEffect, adding to IncomingXP
		if (Props.SourceCharacter->Implements<UPlayerInterface>() && Props.SourceCharacter->Implements<UCombatInterface>())
		{
			const int32 CurrentLevel = ICombatInterface::Execute_GetCharLevel(Props.SourceCharacter);
			const int32 CurrentXP = IPlayerInterface::Execute_GetXP(Props.SourceCharacter);

			const int32 NewLevel = IPlayerInterface::Execute_FindLevelForXP(Props.SourceCharacter, CurrentXP+LocalIncomingXP);

			const int32 NumLevelUps = NewLevel - CurrentLevel;
			if (NumLevelUps > 0)
			{
				const int32 AttributePointsReward = IPlayerInterface::Execute_GetAttributePointsReward(Props.SourceCharacter, CurrentLevel);
				const int32 SpellPointsReward = IPlayerInterface::Execute_GetSpellPointsReward(Props.SourceCharacter, CurrentLevel);

				IPlayerInterface::Execute_AddToPlayerLevel(Props.SourceCharacter, NumLevelUps);
				IPlayerInterface::Execute_AddToAttributePoints(Props.SourceCharacter, AttributePointsReward);
				IPlayerInterface::Execute_AddToSpellPoints(Props.SourceCharacter, SpellPointsReward);

				bTopOffHealth = true;
				bTopOffMana = true;
				
				IPlayerInterface::Execute_LevelUp(Props.SourceCharacter);
			}
			
			IPlayerInterface::Execute_AddToXP(Props.SourceCharacter, LocalIncomingXP);
		}
	}

}

void UAuraAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetMaxHealthAttribute() && bTopOffHealth)
	{
		SetHealth(GetMaxHealth());
		bTopOffHealth = false;
	}
	if (Attribute == GetMaxManaAttribute() && bTopOffMana)
	{
		SetMana(GetMaxMana());
		bTopOffMana = false;
	}
	
}

void UAuraAttributeSet::ShowFloatingText(const FEffectProperties& Props,float Damage, bool bBlockedHit, bool bCritHit) const
{
			if (Props.SourceCharacter != Props.TargetCharacter)
			{
				
				if (AAuraPlayerController* PC = Cast<AAuraPlayerController>(Props.SourceCharacter->Controller))
				{
					PC->ShowDamageNumber(Damage, Props.TargetCharacter, bBlockedHit, bCritHit);
					return;
				}
				if (AAuraPlayerController* PC = Cast<AAuraPlayerController>(Props.TargetCharacter->Controller))
				{
					PC->ShowDamageNumber(Damage, Props.TargetCharacter, bBlockedHit, bCritHit);
				}
				
			}
	
}

void UAuraAttributeSet::SendXPEvent(const FEffectProperties Props)
{
	if(Props.TargetCharacter->Implements<UCombatInterface>())
	{
		const int32 TargetLevel = ICombatInterface::Execute_GetCharLevel(Props.TargetCharacter);
		const ECharacterClass TargetClass = ICombatInterface::Execute_GetCharacterClass(Props.TargetCharacter);

		const int32 XPReward = UAuraAbilitySystemLibrary::GetXPRewardForClassAndLevel(Props.TargetCharacter, TargetClass, TargetLevel);

		const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
		FGameplayEventData Payload;
		Payload.EventTag = GameplayTags.Attributes_Meta_IncomingXP;
		Payload.EventMagnitude = XPReward;
		
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Props.SourceCharacter, GameplayTags.Attributes_Meta_IncomingXP, Payload);
	}
}

//Strength
void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, OldStrength);

}

//Intelligence
void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, OldIntelligence);

}

//Resilience
void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resilience, OldResilience);

}

//Vigor
void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Vigor, OldVigor);

}

void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Armor, OldArmor);

}

void UAuraAttributeSet::OnRep_ArmorPen(const FGameplayAttributeData OldArmorPen) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArmorPen, OldArmorPen);

}

void UAuraAttributeSet::OnRep_Block(const FGameplayAttributeData OldBlock) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Block, OldBlock);

}

void UAuraAttributeSet::OnRep_CritHit(const FGameplayAttributeData OldCritHit) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CritHit, OldCritHit);

}

void UAuraAttributeSet::OnRep_CritDmg(const FGameplayAttributeData OldCritDmg) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CritDmg, OldCritDmg);

}

void UAuraAttributeSet::OnRep_CritResist(const FGameplayAttributeData OldCritResist) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CritResist, OldCritResist);

}

void UAuraAttributeSet::OnRep_HealthRegen(const FGameplayAttributeData OldHealthRegen) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealthRegen, OldHealthRegen);

}

void UAuraAttributeSet::OnRep_ManaRegen(const FGameplayAttributeData OldManaRegen) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ManaRegen, OldManaRegen);

}

void UAuraAttributeSet::OnRep_FireResist(const FGameplayAttributeData OldFireResist) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, FireResist, OldFireResist);

}

void UAuraAttributeSet::OnRep_LightningResist(const FGameplayAttributeData OldLightningResist) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, LightningResist, OldLightningResist);

}

void UAuraAttributeSet::OnRep_ArcaneResist(const FGameplayAttributeData OldArcaneResist) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArcaneResist, OldArcaneResist);

}

void UAuraAttributeSet::OnRep_PhysicalResist(const FGameplayAttributeData OldPhysicalResist) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, PhysicalResist, OldPhysicalResist);

}

//Health
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

//Mana
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

