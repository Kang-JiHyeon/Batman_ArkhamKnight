// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWheeledVehiclePawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ChaosVehicleMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Kismet/KismetSystemLibrary.h"

ABaseWheeledVehiclePawn::ABaseWheeledVehiclePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	BackSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("BackSpringArm"));
	BackSpringArm->SetupAttachment(RootComponent);
	BackSpringArm->SetRelativeLocation(FVector(0.f, 0.f, 75.f));
	BackSpringArm->TargetArmLength = 650.f;
	BackSpringArm->SocketOffset = FVector(0.f, 0.f, 150.f);

	BackCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("BackCamera"));
	BackCamera->SetupAttachment(BackSpringArm);

	FrontSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("FrontSpringArm"));
	FrontSpringArm->SetupAttachment(RootComponent);
	FrontSpringArm->SetRelativeLocation(FVector(30.f, 0.f, 120.f));
	FrontSpringArm->TargetArmLength = 0.f;

	FrontCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FrontCamera"));
	FrontCamera->SetupAttachment(FrontSpringArm);
}

void ABaseWheeledVehiclePawn::BeginPlay()
{
	Super::BeginPlay();

	if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			SubSystem->AddMappingContext(BatMobileMappingContext, 0);
	}

	ChaosVehicleMovementComponent = Cast<UChaosVehicleMovementComponent>(GetVehicleMovementComponent());
}

void ABaseWheeledVehiclePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetMesh() -> SetAngularDamping(UKismetMathLibrary::SelectFloat(0, 3, ChaosVehicleMovementComponent -> IsMovingOnGround()));
}

void ABaseWheeledVehiclePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Throttle, ETriggerEvent::Triggered, this, &ABaseWheeledVehiclePawn::ThrottleTrigger);
		EnhancedInputComponent->BindAction(IA_Throttle, ETriggerEvent::Completed, this, &ABaseWheeledVehiclePawn::ThrottleComplete);
		
		EnhancedInputComponent->BindAction(IA_Brake, ETriggerEvent::Triggered, this, &ABaseWheeledVehiclePawn::BrakeTrigger);
		EnhancedInputComponent->BindAction(IA_Brake, ETriggerEvent::Started, this, &ABaseWheeledVehiclePawn::BrakeStart);
		EnhancedInputComponent->BindAction(IA_Brake, ETriggerEvent::Completed, this, &ABaseWheeledVehiclePawn::BrakeComplete);

		EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ABaseWheeledVehiclePawn::Look);

		EnhancedInputComponent->BindAction(IA_Steering, ETriggerEvent::Triggered, this, &ABaseWheeledVehiclePawn::SteeringTrigger);
		EnhancedInputComponent->BindAction(IA_Steering, ETriggerEvent::Completed, this, &ABaseWheeledVehiclePawn::SteeringComplete);

		EnhancedInputComponent->BindAction(IA_ToggleCamera, ETriggerEvent::Triggered, this, &ABaseWheeledVehiclePawn::ToggleCamera);

		EnhancedInputComponent->BindAction(IA_LockOn, ETriggerEvent::Triggered, this, &ABaseWheeledVehiclePawn::LockOn);
		EnhancedInputComponent->BindAction(IA_Missile, ETriggerEvent::Triggered, this, &ABaseWheeledVehiclePawn::Shot);
	}
}

void ABaseWheeledVehiclePawn::ThrottleTrigger(const FInputActionValue& Value)
{
	ChaosVehicleMovementComponent->SetThrottleInput(Value.Get<float>());
}

void ABaseWheeledVehiclePawn::ThrottleComplete(const FInputActionValue& Value)
{
	ChaosVehicleMovementComponent->SetThrottleInput(Value.Get<float>());
}

void ABaseWheeledVehiclePawn::BrakeTrigger(const FInputActionValue& Value)
{
	ChaosVehicleMovementComponent->SetBrakeInput(Value.Get<float>());
}

void ABaseWheeledVehiclePawn::BrakeStart(const FInputActionValue& Value)
{
	
}

void ABaseWheeledVehiclePawn::BrakeComplete(const FInputActionValue& Value)
{
	ChaosVehicleMovementComponent->SetBrakeInput(Value.Get<float>());
}

void ABaseWheeledVehiclePawn::Look(const FInputActionValue& Value)
{
	FVector2D LookValue = Value.Get<FVector2D>();

	BackSpringArm -> AddRelativeRotation(FRotator(LookValue.Y, LookValue.X, 0));

	float NewPitch = BackSpringArm -> GetRelativeRotation().Pitch;
	float NewYaw = BackSpringArm -> GetRelativeRotation().Yaw;
	FRotator NewRotation = FRotator(UKismetMathLibrary::ClampAngle(NewPitch, -50, 20), NewYaw, 0);
	BackSpringArm -> SetRelativeRotation(NewRotation);
}

void ABaseWheeledVehiclePawn::SteeringTrigger(const FInputActionValue& Value)
{
	ChaosVehicleMovementComponent->SetSteeringInput(Value.Get<float>());
}

void ABaseWheeledVehiclePawn::SteeringComplete(const FInputActionValue& Value)
{
	ChaosVehicleMovementComponent->SetSteeringInput(Value.Get<float>());
}

void ABaseWheeledVehiclePawn::ToggleCamera()
{
	bCameraState = !bCameraState;
	FrontCamera -> Deactivate();
	BackCamera -> Deactivate();

	if (bCameraState)
	{
		FrontCamera -> Activate();
	}
	else
	{
		BackCamera -> Activate();
	}
}

void ABaseWheeledVehiclePawn::LockOn(const FInputActionValue& Value)
{
	
}

void ABaseWheeledVehiclePawn::Shot(const FInputActionValue& Value)
{
	
}