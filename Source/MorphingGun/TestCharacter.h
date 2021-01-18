// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestCharacter.generated.h"

UCLASS()
class MORPHINGGUN_API ATestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	UChildActorComponent* WeaponActor;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "WeaponActor")
	TSubclassOf<class AMorphingGunWeapon> WeaponActorAsset;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	USceneComponent* MuzzleLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseLookUpAtRate;

	// Gun muzzle's offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	// Projectile's class to spawn.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile)
	TSubclassOf<class AMorphingGunProjectile> ProjectileClass;

	UFUNCTION()
	void Fire();

private:
	void MoveForward(float value);
	void MoveRight(float value);
	void LookUpAtRate(float value);
	void TurnAtRate(float value);
};