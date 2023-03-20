// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseShip.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABaseShip::ABaseShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add Mesh
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	AddOwnedComponent(StaticMeshComponent);

	RootComponent = StaticMeshComponent;
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // avoid rotating when the character does
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));

	// Create a camera...
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}

// Called when the game starts or when spawned
void ABaseShip::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Fly up
		EnhancedInputComponent->BindAction(FlyUpAction, ETriggerEvent::Triggered, this, &ABaseShip::FlyUp);

		// Fly down
		EnhancedInputComponent->BindAction(FlyDownAction, ETriggerEvent::Triggered, this, &ABaseShip::FlyDown);

		// Move
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABaseShip::Move);
		
		// Look
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABaseShip::Look);

		// Use
		EnhancedInputComponent->BindAction(UseAction, ETriggerEvent::Triggered, this, &ABaseShip::Unpossess);

		// Zoom Camera
		EnhancedInputComponent->BindAction(CameraZoomAction, ETriggerEvent::Triggered, this, &ABaseShip::ZoomCamera);
	}

}

void ABaseShip::ZoomCamera(const FInputActionValue& Value)
{
	if (Controller)
	{
		const float ScrollValue = Value.Get<float>();
		
		// raycast and check hit objects
		const float NewCameraZoom =  FMath::Clamp(CameraBoom->TargetArmLength + ScrollValue * CameraZoomMultiplier, MinCameraZoom, MaxCameraZoom);
		CameraBoom->TargetArmLength = NewCameraZoom;
	}
}

void ABaseShip::Use(APawn* Pawn)
{
	Possess(Pawn);
}

void ABaseShip::OnPossess()
{
	SetupInput();
}

void ABaseShip::OnUnPossess()
{
	Driver = nullptr;
}

void ABaseShip::Possess(APawn* Pawn)
{
	if (Pawn->Controller)
	{
		Driver = Pawn;
		Pawn->Controller->Possess(this);
	}
}

void ABaseShip::Unpossess()
{
	if (Controller)
	{
		RemoveInput();
		Controller->Possess(Driver);
	}
}

void ABaseShip::SetupInput()
{
	// Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
}

void ABaseShip::RemoveInput()
{
	// Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(MappingContext);
		}
	}
}

void ABaseShip::FlyUp(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Up!"));
	if (Controller)
	{
		StaticMeshComponent->AddForce(FVector::UpVector * 50000.f);
	}
}

void ABaseShip::FlyDown(const FInputActionValue& Value)
{
	if (Controller)
	{
		UE_LOG(LogTemp, Warning, TEXT("Down!"));
		StaticMeshComponent->AddForce(FVector::UpVector * -50000.f);
	}
}

void ABaseShip::Move(const FInputActionValue& Value)
{
	const FVector2d MovementVector = Value.Get<FVector2d>();
	
	if (Controller)
	{
		// get forward rotator
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		// forward movement
		const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector ForwardForce = Forward * 500000.f * MovementVector.Y;

		// right movement
		const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		const FVector RightForce = Right * 500000.f * MovementVector.X;
		
		StaticMeshComponent->AddForce(ForwardForce + RightForce);
	}
}

void ABaseShip::Look(const FInputActionValue& Value)
{
	if (Controller)
	{
		// input is a Vector2D
		const FVector2D LookAxisVector = Value.Get<FVector2D>();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *LookAxisVector.ToString());
		
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

