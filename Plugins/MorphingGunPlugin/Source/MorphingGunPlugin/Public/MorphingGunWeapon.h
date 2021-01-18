// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MorphingGunWeapon.generated.h"

UCLASS()
class MORPHINGGUNPLUGIN_API AMorphingGunWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMorphingGunWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Gun SkeletalMeshComponent
	UPROPERTY(EditAnywhere, Category = "Skeletal Mesh")
	class USkeletalMeshComponent* GunMesh;
};
