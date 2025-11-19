// vib -- CC0

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/TerraArcanaTypes.h"
#include "Projectile.generated.h"

UCLASS()
class TERRA_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "Projectile")
	FProjectileDefinition ProjectileDefinition;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USphereComponent> Sphere;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class UGameplayEffect>> EffectsToApply;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
