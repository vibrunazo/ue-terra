// vib -- CC0

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "TerraDeveloperSettings.generated.h"

class UGameplayEffect;
/**
 * 
 */
UCLASS(config = Game, DefaultConfig, meta = (DisplayName = "Terra Ability Settings"))
class TERRA_API UTerraDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Config, EditDefaultsOnly, Category = "Ability Defaults", meta = (DisplayName = "NoMove Effect"))
	TSoftClassPtr<UGameplayEffect> NoMoveEffect;
	
};
