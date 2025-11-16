// vib -- CC0

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Data/TerraArcanaTypes.h"
#include "TerraAbility.generated.h"

/**
 * 
 */
UCLASS()
class TERRA_API UTerraAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	// Set Ability Definition
	UFUNCTION(BlueprintCallable, Category = "Configuration")
	void SetAbilityDefinition(const FAbilityDefinition& InAbilityDefinition);
	
	// Ability Definition
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
	FAbilityDefinition AbilityDefinition;

	UFUNCTION(BlueprintCallable, Category = "Effects")
	void ApplySelfEffects();

	UFUNCTION(BlueprintCallable, Category = "Effects")
	void RemoveSelfEffects();

private:
	UPROPERTY()
	TArray<FActiveGameplayEffectHandle> ActiveSelfEffects;
	
protected:
	// Override Activate Ability and End Ability
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
};
