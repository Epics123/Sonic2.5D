// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SonicMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SONIC2_5D_API USonicMovementComponent : public UCharacterMovementComponent
{
	GENERATED_UCLASS_BODY()
	
public:
	float GroundSpeed = 0.0f;
	float Acc = 0.046875;
	float Dec = 0.5f;
	float Frc = 0.046875;
	float TopSpeed = 6.0f;
	float SlopeFactor = 0.125f;
	float SlopeRollUp = 0.078125f;
	float SlopeRollDown = 0.3125f;
	float Fall = 2.5f; // tolerance ground speed for sticking to walls and ceilings

	float AirAcc = 0.09375f;
	float JumpForce = 6.5f;
	float Grv = 0.21875;
};
