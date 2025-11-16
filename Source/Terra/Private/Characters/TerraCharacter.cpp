// vib -- CC0


#include "Characters/TerraCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/TerraAbilitySystemComponent.h"
#include "AbilitySystem/TerraAttributeSet.h"
#include "AbilitySystem/TerraAbility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATerraCharacter::ATerraCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Configure character movement
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	AbilitySystemComponent = CreateDefaultSubobject<UTerraAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UTerraAttributeSet>(TEXT("AttributeSet"));

}

// Called when the game starts or when spawned
void ATerraCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GiveCoreAbilities();
}

void ATerraCharacter::GiveCoreAbilities()
{
	if(!AbilitySystemComponent || CoreAbilities.Num() == 0) return;

	for(const TSubclassOf<UTerraAbility> AbilityClass : CoreAbilities)
	{
		FGameplayAbilitySpec AbilitySpec(AbilityClass, 1);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}

// Called every frame
void ATerraCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LookAtTargetLocation();
}

void ATerraCharacter::LookAtTargetLocation()
{
	if (bShouldLookAtTarget)
	{
		// if current movement speed is zero, return
		if (GetCharacterMovement()->Velocity.Size() <= 0.1f)
		{
			return;
		}
		
		if (AController* PlayerController = GetController())
		{
			const FVector Location = GetActorLocation();
			const FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Location, TargetLocation);
			PlayerController->SetControlRotation(FRotator(0.f, LookAtRotation.Yaw, 0.f));
		}
	}
}

// Called to bind functionality to input
void ATerraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATerraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilitySystemComponent();
}

void ATerraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilitySystemComponent();
}

void ATerraCharacter::InitAbilitySystemComponent()
{
	if (!AbilitySystemComponent)
	{
		return;
	}
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UTerraAttributeSet::GetMoveSpeedAttribute()).AddUObject(this, &ATerraCharacter::OnMoveSpeedChanged);

	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		BaseMoveSpeed = MovementComponent->MaxWalkSpeed;
		BaseRotationRate = MovementComponent->RotationRate.Yaw;
	}
}

void ATerraCharacter::OnMoveSpeedChanged(const FOnAttributeChangeData& Data)
{
	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		const float Multiplier = Data.NewValue / 100.0f;
		MovementComponent->MaxWalkSpeed = BaseMoveSpeed * Multiplier;

		FRotator NewRotationRate = MovementComponent->RotationRate;
		NewRotationRate.Yaw = BaseRotationRate * Multiplier;
		MovementComponent->RotationRate = NewRotationRate;
	}
}

UAbilitySystemComponent* ATerraCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATerraCharacter::UseAbility(int32 AbilityIndex)
{
	if (AbilitySystemComponent)
	{
		FGameplayTagContainer TagContainer;
		FGameplayTag EventTag = FGameplayTag::RequestGameplayTag(FName(*FString::Printf(TEXT("Event.Ability.%d"), AbilityIndex)));
		TagContainer.AddTag(EventTag);
		
		AbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);
	}
}

