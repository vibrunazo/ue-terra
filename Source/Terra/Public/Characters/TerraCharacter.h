// vib -- CC0

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "TerraCharacter.generated.h"

class UTerraAttributeSet;
class UTerraAbilitySystemComponent;
class UTerraAbility;

UCLASS()
class TERRA_API ATerraCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATerraCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	//~ Begin IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface
	
	// Use Ability
	void UseAbility(int32 AbilityIndex);
	
	// World location the character is looking at if bShouldLookAtTarget is true
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rotation")
	FVector TargetLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rotation")
	bool bShouldLookAtTarget = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void LookAtTargetLocation();

	void GiveCoreAbilities();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<UTerraAbility>> CoreAbilities;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTerraAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UTerraAttributeSet> AttributeSet;

};
