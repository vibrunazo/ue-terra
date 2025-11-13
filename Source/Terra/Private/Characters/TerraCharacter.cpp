// vib -- CC0


#include "Characters/TerraCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/TerraAbilitySystemComponent.h"
#include "AbilitySystem/TerraAttributeSet.h"
#include "AbilitySystem/TerraAbility.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ATerraCharacter::ATerraCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Configure character movement
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
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

}

// Called to bind functionality to input
void ATerraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATerraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void ATerraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
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

