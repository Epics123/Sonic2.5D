// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SonicCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SONIC2_5D_API ASonicCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	ASonicCharacter(const FObjectInitializer& ObjectInitializer);

	void UpdateAnimations();
	void UpdateSpriteRotation(float speed);

protected:
	/** Called for side to side input */
	void MoveRight(float Value);

	void Jump();

	void StopJump();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, class UPaperFlipbook*> Animations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbookComponent* PlayerSprite;

	class USonicMovementComponent* MovementComponent;

private:
	float GroundSpeed = 0.0f;
	float Acc = 1.40625f;//0.046875f;
	float Dec = 15.0f;//0.5f;
	float Frc = 1.40625f;//0.046875;
	float TopSpeed = 600.0f;//6.0f;
	float SlopeFactor = 0.125f;
	float SlopeRollUp = 0.078125f;
	float SlopeRollDown = 0.3125f;
	float Fall = 2.5f; // tolerance ground speed for sticking to walls and ceilings

	float AirAcc = 0.09375f;
	float JumpForce = 6.5f;
	float Grv = 0.21875;
};
