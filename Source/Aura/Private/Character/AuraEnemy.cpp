// Copyright © 2023 Jodiah Jensen


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"
#include "Components/WidgetComponent.h"
#include "UI/Widgets/AuraUserWidget.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
	
}

void AAuraEnemy::HighlightActor()
{
	//highlight actor mesh
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	//include weapon for highlighting
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
}

void AAuraEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 AAuraEnemy::GetCharLevel()
{
	return Level;
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilityActorInfo();

	if (UAuraUserWidget* AuraUserWidget = Cast<UAuraUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		AuraUserWidget->SetWidgetController(this);
	}
	
	UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(AttributeSet);
	if (AuraAS)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

		OnHealthChanged.Broadcast(AuraAS->GetHealth());
		OnMaxHealthChanged.Broadcast(AuraAS->GetMaxHealth());
	}
	
}

void AAuraEnemy::InitAbilityActorInfo()
{
//	Super::InitAbilityActorInfo();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	InitializeDefaultAttributes();
}

void AAuraEnemy::InitializeDefaultAttributes() const
{
	UAuraAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}
