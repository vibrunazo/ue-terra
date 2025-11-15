// vib -- CC0


#include "AbilitySystem/TerraAttributeSet.h"

#include "Net/UnrealNetwork.h"

UTerraAttributeSet::UTerraAttributeSet()
{
	Health = 100.f;
	MaxHealth = 100.f;
	Mana = 50.f;
	MaxMana = 100.f;
	Strength = 10.f;
	Agility = 10.f;
	Intelligence = 10.f;
	MoveSpeed = 100.f;
	
}

void UTerraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UTerraAttributeSet, Health);
	DOREPLIFETIME(UTerraAttributeSet, MaxHealth);
	DOREPLIFETIME(UTerraAttributeSet, Mana);
	DOREPLIFETIME(UTerraAttributeSet, MaxMana);
	DOREPLIFETIME(UTerraAttributeSet, Strength);
	DOREPLIFETIME(UTerraAttributeSet, Agility);
	DOREPLIFETIME(UTerraAttributeSet, Intelligence);
	DOREPLIFETIME(UTerraAttributeSet, MoveSpeed);
}

void UTerraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTerraAttributeSet, Health, OldHealth);
}

void UTerraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTerraAttributeSet, MaxHealth, OldMaxHealth);
}

void UTerraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTerraAttributeSet, Mana, OldMana);
}

void UTerraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTerraAttributeSet, MaxMana, OldMaxMana);
}

void UTerraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTerraAttributeSet, Strength, OldStrength);
}

void UTerraAttributeSet::OnRep_Agility(const FGameplayAttributeData& OldAgility)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTerraAttributeSet, Agility, OldAgility);
}

void UTerraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTerraAttributeSet, Intelligence, OldIntelligence);
}

void UTerraAttributeSet::OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTerraAttributeSet, MoveSpeed, OldMoveSpeed);
}
