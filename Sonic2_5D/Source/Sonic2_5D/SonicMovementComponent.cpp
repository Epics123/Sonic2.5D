// Fill out your copyright notice in the Description page of Project Settings.


#include "SonicMovementComponent.h"

USonicMovementComponent::USonicMovementComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	MaxAcceleration = Acc;
	BrakingFrictionFactor = Frc;
	MaxWalkSpeed = TopSpeed;
}
