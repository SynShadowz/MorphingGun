// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"
#include "Camera/CameraComponent.h"
#include "MorphingGunProjectile.h"
#include "MorphingGunWeapon.h"

// Sets default values
ATestCharacter::ATestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetRootComponent());

	WeaponActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("MorphingGun"));
	WeaponActor->SetupAttachment(GetRootComponent());
	WeaponActor->SetChildActorClass(WeaponActorAsset);

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(WeaponActor);

	MuzzleOffset = FVector(100.f, 0.f, 10.f);

	BaseLookUpAtRate = 45.f;
	BaseTurnRate = 45.f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATestCharacter::Fire);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATestCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ATestCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATestCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ATestCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &ATestCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis(TEXT("TurnRate"), this, &ATestCharacter::TurnAtRate);
}

void ATestCharacter::Fire()
{
	// Attempt to fire a projectile
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FRotator SpawnRotation = GetControlRotation();
			// Muzzle offset is in camera space, so transform it into world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = ((MuzzleLocation != nullptr) ? MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(MuzzleOffset);

			// Set spawn collision handling override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// Spawn the projectile at the muzzle
			World->SpawnActor<AMorphingGunProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
}

void ATestCharacter::MoveForward(float value)
{
	if ((Controller) && (value != 0.0f))
	{
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

void ATestCharacter::MoveRight(float value)
{
	if ((Controller) && (value != 0.0f))
	{
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}
}

void ATestCharacter::LookUpAtRate(float value)
{
	AddControllerPitchInput(value * BaseLookUpAtRate * GetWorld()->GetDeltaSeconds());
}

void ATestCharacter::TurnAtRate(float value)
{
	AddControllerYawInput(value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}
