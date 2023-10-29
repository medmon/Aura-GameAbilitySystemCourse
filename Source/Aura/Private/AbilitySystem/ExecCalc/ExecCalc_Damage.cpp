// Copyright © 2023 Jodiah Jensen


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraAbilityTypes.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"

struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPen);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Block);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritHit);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritDmg);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritResist);
	
	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPen, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Block, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CritHit, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CritDmg, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CritResist, Target, false);
	}
};

static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatics;
	return DStatics;
	
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritHitDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritDmgDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritResistDef);

}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatar);
	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatar);
	
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	
	//capture some attributes, don't forget to capture in the constructor

	//Get Damage Set by Caller Magnitude
	float Damage = Spec.GetSetByCallerMagnitude(FAuraGameplayTags::Get().Damage);

		
	/* Capture BlockChance on Target and determine if there was a successful block
	 * if block, halve the damage
	 * Do Block calculation first
	 */

	// Get Block Chance
	float Block = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockDef, EvaluationParameters, Block);
	Block = FMath::Max<float>(0.f, Block);

	// Determine if block is successful
	
	const bool bBlocked = FMath::RandRange(1,100) < Block;

	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
	UAuraAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, bBlocked);
	
	
	// Modify damage
	if(bBlocked)
	{
		Damage = Damage / 2;
	}

	// End of Block calculations

	// calculate effect or armor and armor penetration
	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluationParameters, TargetArmor);
	TargetArmor = FMath::Max<float>(0.f, TargetArmor);

	float SourceArmorPen = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenDef, EvaluationParameters, SourceArmorPen);
	SourceArmorPen = FMath::Max<float>(0.f, SourceArmorPen);

	const UCharacterClassInfo* CharacterClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);
	const FRealCurve* ArmorPenetrationCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString());
	const float ArmorPenCoefficient = ArmorPenetrationCurve->Eval(SourceCombatInterface->GetCharLevel());
	
	//armor penetration ignores a percentage of target armor
	const float EffectiveArmor = TargetArmor * (100-SourceArmorPen * ArmorPenCoefficient) / 100.f;

	const FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"), FString());
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetCombatInterface->GetCharLevel());

	//armor ignores a percentage of incoming damage
	Damage *= (100- EffectiveArmor * EffectiveArmorCoefficient) /100.f;

	//end armor calculations

	//Critical Hit calculations
	float CritHit = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritHitDef, EvaluationParameters, CritHit);
	CritHit = FMath::Max<float>(0.f, CritHit);

	float CritDmg = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritDmgDef, EvaluationParameters, CritDmg);
	CritDmg = FMath::Max<float>(0.f, CritDmg);

	float TargetCritResist = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritResistDef, EvaluationParameters, TargetCritResist);
	TargetCritResist = FMath::Max<float>(0.f, TargetCritResist);

	//do the math for critical hits

	//get crit resist coefficient from curve table
	CharacterClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(TargetAvatar);
	const FRealCurve* CritResistanceCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("CritResistance"), FString());
	const float CritResistCoefficient = CritResistanceCurve->Eval(TargetCombatInterface->GetCharLevel());

	
	//TargetCritResist reduces CritHit chance by a certain percentage
	const float EffectiveCritHit = CritHit - TargetCritResist * CritResistCoefficient;
	const bool bCritHit = FMath::RandRange(1, 100) < EffectiveCritHit;

	
	UAuraAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bCritHit);

	
	//double damage + bonus if roll was successful
	Damage = bCritHit ? Damage * 2.f + CritDmg : Damage;

	
	/*
	 * output the damage
	 */
	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
	
}
