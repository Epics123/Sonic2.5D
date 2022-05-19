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
	ASonicCharacter();

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
};
