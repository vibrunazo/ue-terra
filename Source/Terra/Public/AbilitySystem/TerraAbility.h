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
	// Ability Definition
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
	FAbilityDefinition AbilityDefinition;
	
};
