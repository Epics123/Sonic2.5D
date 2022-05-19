// Fill out your copyright notice in the Description page of Project Settings.


#include "SonicCharacter.h"

ASonicCharacter::ASonicCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Camera setup
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);
}

void ASonicCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
	}
}

void ASonicCharacter::Jump()
{
	ACharacter::Jump();
}

void ASonicCharacter::StopJump()
{
	ACharacter::StopJumping();
}

void ASonicCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASonicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &ASonicCharacter::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASonicCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ASonicCharacter::StopJump);
}

void ASonicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
