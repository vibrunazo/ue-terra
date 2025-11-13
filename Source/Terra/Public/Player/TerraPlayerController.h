// vib -- CC0

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "TerraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class TERRA_API ATerraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	// Sets default values for this player controller's properties
	ATerraPlayerController();

	// Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	// Input Action Move
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;

	// Input Action Ability 1
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* Ability1Action;

	// Input Action Ability 2
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* Ability2Action;

	// Input Action Ability 3
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* Ability3Action;

	// Input Action Ability 4
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* Ability4Action;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

	void TriggeredMove(const FInputActionValue& InputActionValue);
	void TriggeredAbility1(const FInputActionValue& InputActionValue);
	void TriggeredAbility2(const FInputActionValue& InputActionValue);
	void TriggeredAbility3(const FInputActionValue& InputActionValue);
	void TriggeredAbility4(const FInputActionValue& InputActionValue);
};
