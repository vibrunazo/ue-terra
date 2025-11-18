// vib -- CC0

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Data/TerraArcanaTypes.h"
#include "TerraAIController.generated.h"

class UStateTreeAIComponent;

/**
 * 
 */
UCLASS()
class TERRA_API ATerraAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATerraAIController();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UStateTreeAIComponent> StateTreeAIComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	FAIDefinition AIDefinition;
	
protected:
	virtual void OnPossess(APawn* InPawn) override;

};
