// vib -- CC0


#include "AI/TerraAIController.h"
#include "Components/StateTreeAIComponent.h"

ATerraAIController::ATerraAIController()
{
	StateTreeAIComponent = CreateDefaultSubobject<UStateTreeAIComponent>(TEXT("StateTreeAIComponent"));
}

void ATerraAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}
