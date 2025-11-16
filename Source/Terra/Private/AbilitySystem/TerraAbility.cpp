// vib -- CC0


#include "AbilitySystem/TerraAbility.h"
#include "AbilitySystemComponent.h"

void UTerraAbility::SetAbilityDefinition(const FAbilityDefinition& InAbilityDefinition)
{
	AbilityDefinition = InAbilityDefinition;
}

void UTerraAbility::ApplySelfEffects()
{
	if (const FGameplayAbilityActorInfo* ActorInfo = GetCurrentActorInfo())
	{
		if (UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get())
		{
			for (const TSoftClassPtr<UGameplayEffect>& EffectClassPtr : AbilityDefinition.SelfEffectClasses)
			{
				if (TSubclassOf<UGameplayEffect> EffectClass = EffectClassPtr.LoadSynchronous())
				{
					FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
					EffectContext.AddSourceObject(this);

					FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(EffectClass, GetAbilityLevel(), EffectContext);
					if (SpecHandle.IsValid())
					{
						FActiveGameplayEffectHandle ActiveHandle = ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
						if (ActiveHandle.WasSuccessfullyApplied())
						{
							ActiveSelfEffects.Add(ActiveHandle);
						}
					}
				}
			}
		}
	}
}

void UTerraAbility::RemoveSelfEffects()
{
	if (const FGameplayAbilityActorInfo* ActorInfo = GetCurrentActorInfo())
	{
		if (UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get())
		{
			for (const FActiveGameplayEffectHandle& ActiveHandle : ActiveSelfEffects)
			{
				if (ActiveHandle.IsValid())
				{
					ASC->RemoveActiveGameplayEffect(ActiveHandle);
				}
			}
			ActiveSelfEffects.Empty();
		}
	}
}

void UTerraAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	ApplySelfEffects();
}

void UTerraAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	RemoveSelfEffects();
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

