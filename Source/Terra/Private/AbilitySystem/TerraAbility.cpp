// vib -- CC0


#include "AbilitySystem/TerraAbility.h"
#include "AbilitySystemComponent.h"

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

