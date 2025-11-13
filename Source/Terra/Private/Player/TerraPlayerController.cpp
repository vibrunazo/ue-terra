// vib -- CC0


#include "Player/TerraPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Characters/TerraCharacter.h"

ATerraPlayerController::ATerraPlayerController()
{
}

void ATerraPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATerraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// Add input mapping context
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Setup Action Bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATerraPlayerController::TriggeredMove);
		EnhancedInputComponent->BindAction(Ability1Action, ETriggerEvent::Triggered, this, &ATerraPlayerController::TriggeredAbility1);
		EnhancedInputComponent->BindAction(Ability2Action, ETriggerEvent::Triggered, this, &ATerraPlayerController::TriggeredAbility2);
		EnhancedInputComponent->BindAction(Ability3Action, ETriggerEvent::Triggered, this, &ATerraPlayerController::TriggeredAbility3);
		EnhancedInputComponent->BindAction(Ability4Action, ETriggerEvent::Triggered, this, &ATerraPlayerController::TriggeredAbility4);
		
	}
}

void ATerraPlayerController::TriggeredMove(const FInputActionValue& InputActionValue)
{
	const FVector2D InputVector = InputActionValue.Get<FVector2D>();

	if (APawn* ControlledPawn = GetPawn())
	{
		// Forward/Backward Movement (World X-axis)
		ControlledPawn->AddMovementInput(FVector(1.0f, 0.0f, 0.0f), InputVector.Y);
		// Right/Left Movement (World Y-axis)
		ControlledPawn->AddMovementInput(FVector(0.0f, 1.0f, 0.0f), InputVector.X);
	}
}

void ATerraPlayerController::TriggeredAbility1(const FInputActionValue& InputActionValue)
{
	if (ATerraCharacter* TerraCharacter = Cast<ATerraCharacter>(GetPawn()))
	{
		TerraCharacter->UseAbility(1);
	}
}

void ATerraPlayerController::TriggeredAbility2(const FInputActionValue& InputActionValue)
{
	if (ATerraCharacter* TerraCharacter = Cast<ATerraCharacter>(GetPawn()))
	{
		TerraCharacter->UseAbility(2);
	}
	
}

void ATerraPlayerController::TriggeredAbility3(const FInputActionValue& InputActionValue)
{
	if (ATerraCharacter* TerraCharacter = Cast<ATerraCharacter>(GetPawn()))
	{
		TerraCharacter->UseAbility(3);
	}
}

void ATerraPlayerController::TriggeredAbility4(const FInputActionValue& InputActionValue)
{
	if (ATerraCharacter* TerraCharacter = Cast<ATerraCharacter>(GetPawn()))
	{
		TerraCharacter->UseAbility(4);
	}
}
