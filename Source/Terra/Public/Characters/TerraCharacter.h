// vib -- CC0

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TerraCharacter.generated.h"

UCLASS()
class TERRA_API ATerraCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATerraCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
