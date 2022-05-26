// Fill out your copyright notice in the Description page of Project Settings.


#include "SonicCharacter.h"
#include "SonicMovementComponent.h"

#include "Paper2D/Classes/PaperFlipbookComponent.h"
#include "Math/UnrealMathUtility.h"

ASonicCharacter::ASonicCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<USonicMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PlayerSprite"));
	PlayerSprite->SetupAttachment(RootComponent);

	// Camera setup
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);

	MovementComponent = Cast<USonicMovementComponent>(GetMovementComponent());
}

void ASonicCharacter::UpdateAnimations()
{
	UPaperFlipbook* NextAnim = nullptr;
	if (GroundSpeed == 0.0f)
	{
		NextAnim = *Animations.Find("Idle");
		if(NextAnim)
			PlayerSprite->SetFlipbook(NextAnim);
		PlayerSprite->SetPlayRate(1.0f);
	}
	if (FMath::Abs(GroundSpeed) > 0.0f && FMath::Abs(GroundSpeed) < TopSpeed && !Skidding)
	{
		NextAnim = *Animations.Find("Jog");
		if (NextAnim)
			PlayerSprite->SetFlipbook(NextAnim);
		
		UpdateSpriteRotation(GroundSpeed);
		PlayerSprite->SetPlayRate((FMath::Abs(GroundSpeed) / TopSpeed) + 0.1f);
		
	}
	if (FMath::Abs(GroundSpeed) >= TopSpeed && !Skidding)
	{
		NextAnim = *Animations.Find("Run");
		if (NextAnim)
			PlayerSprite->SetFlipbook(NextAnim);

		UpdateSpriteRotation(GroundSpeed);
	}
	if (Skidding)
	{
		NextAnim = *Animations.Find("Skid");
		if (NextAnim)
			PlayerSprite->SetFlipbook(NextAnim);

		//UpdateSpriteRotation(GroundSpeed);
	}
}

void ASonicCharacter::UpdateSpriteRotation(float speed)
{
	int sign = (int)FMath::Sign(speed);
	switch (sign)
	{
	case 1:
		PlayerSprite->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		break;
	case -1:
		PlayerSprite->SetRelativeRotation(FRotator(0.0f, -180.0f, 0.0f));
		break;
	}
}

void ASonicCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr))
	{
		// Left is pressed
		if (Value < 0.0f)
		{
			// Are we moving to the right already?
			if (GroundSpeed > 0)
			{
				if(GroundSpeed >= 400.0f)
					Skidding = true;
				GroundSpeed -= Dec;
				if(GroundSpeed <= 0)
					GroundSpeed = -0.5f;
			}
			// Are we moving left?
			else if (GroundSpeed > -TopSpeed)
			{
				Skidding = false;
				GroundSpeed -= Acc;
				if(GroundSpeed <= -TopSpeed)
					GroundSpeed = -TopSpeed;
			}
			
			FVector CurrentLocation = GetActorLocation();
			float dt = GetWorld()->GetDeltaSeconds();
			CurrentLocation.X += GroundSpeed * dt;
			SetActorLocation(CurrentLocation);
		}

		// Right is pressed
		if (Value > 0.0f)
		{
			// Are we moving to the left already?
			if (GroundSpeed < 0)
			{
				if (GroundSpeed <= -400.0f)
					Skidding = true;
				GroundSpeed += Dec;
				if (GroundSpeed >= 0)
					GroundSpeed = 0.5f;
			}
			// Are we moving right?
			else if (GroundSpeed < TopSpeed)
			{
				Skidding = false;
				GroundSpeed += Acc;
				if (GroundSpeed >= TopSpeed)
					GroundSpeed = TopSpeed;
			}

			FVector CurrentLocation = GetActorLocation();
			float dt = GetWorld()->GetDeltaSeconds();
			CurrentLocation.X += GroundSpeed * dt;
			SetActorLocation(CurrentLocation);
		}
		
		if (Value == 0.0f)
		{
			Skidding = false;
			GroundSpeed -= fmin(fabs(GroundSpeed), Frc) * FMath::Sign(GroundSpeed);
			
			FVector CurrentLocation = GetActorLocation();
			float dt = GetWorld()->GetDeltaSeconds();
			CurrentLocation.X += GroundSpeed * dt;
			SetActorLocation(CurrentLocation);
		}
			
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

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), GroundSpeed));
	UpdateAnimations();
}
