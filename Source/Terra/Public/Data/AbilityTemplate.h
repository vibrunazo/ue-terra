// vib -- CC0

#pragma once

#include "CoreMinimal.h"
#include "TerraArcanaTypes.h"
#include "Engine/DataAsset.h"
#include "AbilityTemplate.generated.h"

/**
 * Data Asset for an ability.
 * This is the template for creating new ability assets.
 */
UCLASS(BlueprintType)
class TERRA_API UAbilityTemplate : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	// The name of the ability.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	FText AbilityName;

	// The description of the ability.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	FText AbilityDescription;

	// The icon for the ability.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	TSoftObjectPtr<UTexture2D> AbilityIcon;

	// The GameplayAbility class to grant.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	TSoftClassPtr<UTerraAbility> AbilityClass;

	// The GameplayAbility class to grant.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	FAbilityDefinition AbilityDefinition;
};
