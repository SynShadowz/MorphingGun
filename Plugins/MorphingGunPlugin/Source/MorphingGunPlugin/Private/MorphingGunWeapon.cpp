// Fill out your copyright notice in the Description page of Project Settings.


#include "MorphingGunWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "MorphingGunProjectile.h"

// Sets default values
AMorphingGunWeapon::AMorphingGunWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Skeletal Mesh"));
	GunMesh->SetupAttachment(GetRootComponent());
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> GunMeshComponentAsset(TEXT("SkeletalMesh'/MorphingGunPlugin/Weapon/Meshes/SK_FPGun.SK_FPGun'"));

	if (GunMeshComponentAsset.Succeeded())
	{
		GunMesh->SetSkeletalMesh(GunMeshComponentAsset.Object);
	}

}

// Called when the game starts or when spawned
void AMorphingGunWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMorphingGunWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}