#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "TerraDeveloperSettings.h"
#include "Engine/DataAsset.h"
#include "TerraArcanaTypes.generated.h"

class UNiagaraSystem;
class UGameplayAbility;
class UGameplayEffect;
class UAnimMontage;
class UTexture2D;
class UTerraAbility;

USTRUCT(BlueprintType)
struct FProjectileDefinition
{
	GENERATED_BODY()

	// Tag to trigger the projectile.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	FGameplayTag TriggerTag;

	// Magnitude of the projectile.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	float Magnitude = 10.f;

	// Effect Classes the projectile applies to targets.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	TArray<TSoftClassPtr<UGameplayEffect>> EffectClasses;

	// Speed the projectile travels at.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	float Speed = 0.f;

	// Lifespan of the projectile.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	float Lifespan = 0.2f;

	// Niagara VFX to play while the projectile is in flight.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	TSoftObjectPtr<UNiagaraSystem> TravelVFX;

	// Niagara VFX to play when the projectile hits a target.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	TSoftObjectPtr<UNiagaraSystem> ImpactVFX;
};

USTRUCT(BlueprintType)
struct FDashDefinition
{
	GENERATED_BODY()

	// Tag to trigger the projectile.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dash")
	FGameplayTag TriggerTag;

	// Dash Distance
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dash")
	float Distance = 1200.f;

	// Dash Duration
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dash")
	float Duration = 0.5f;

};

USTRUCT(BlueprintType)
struct FAbilityDefinition
{
	GENERATED_BODY()

	// The montage to play for this ability.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	TSoftObjectPtr<UAnimMontage> AbilityMontage;

	// Effects to apply to the owner of the ability.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	TArray<TSoftClassPtr<UGameplayEffect>> SelfEffectClasses;

	// Projectiles to use for this ability.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	TArray<FProjectileDefinition> Projectiles;

	// Dashes to use for this ability.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	TArray<FDashDefinition> Dashes;
	
	FAbilityDefinition()
	{
		// Get the singleton instance of your settings class
		const UTerraDeveloperSettings* Settings = GetDefault<UTerraDeveloperSettings>();

		// Check if the setting is valid and not null
		if (Settings && !Settings->NoMoveEffect.IsNull())
		{
			// Add the designer-defined default effect to this array
			SelfEffectClasses.Add(Settings->NoMoveEffect);
		}
	}
};


/**
 * Represents a player's configured instance of an ability.
 * This is what gets saved to JSON.
 */
USTRUCT(BlueprintType)
struct FAbilityInstance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	FPrimaryAssetId AbilityTemplateID;

	// The level of the ability instance.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	int32 Level;

};

