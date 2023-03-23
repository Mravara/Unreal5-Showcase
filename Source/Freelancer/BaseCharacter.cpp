// Copyrighted by Binx Games.


#include "BaseCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "FPlayerCameraManager.h"
#include "Usable.h"

// Sets default values
ABaseCharacter::ABaseCharacter(const FObjectInitializer& OI)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create Camera Manager
	PlayerCameraManager = CreateDefaultSubobject<UFPlayerCameraManager>(TEXT("Player Camera Managerz"));
	AddOwnedComponent(PlayerCameraManager);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	//
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
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerCameraManager->Init(FollowCamera, CameraBoom);
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jump
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Move
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Move);
		
		// Look
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Look);

		// Use
		EnhancedInputComponent->BindAction(UseAction, ETriggerEvent::Triggered, this, &ABaseCharacter::UseObject);

		// Zoom Camera
		EnhancedInputComponent->BindAction(CameraZoomAction, ETriggerEvent::Triggered, this, &ABaseCharacter::ZoomCamera);
	}
}

void ABaseCharacter::OnPossess()
{
	SetupInput();
}

void ABaseCharacter::OnUnPossess()
{
	RemoveInput();
}

void ABaseCharacter::SetupInput()
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

void ABaseCharacter::RemoveInput()
{
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(MappingContext);
		}
	}
}

void ABaseCharacter::Move(const FInputActionValue& Value)
{
	const FVector2d MovementVector = Value.Get<FVector2d>();

	if (Controller)
	{
		// get forward rotator
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		// forward movement
		const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Forward, MovementVector.Y);

		// right movement
		const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Right, MovementVector.X);
	}
}

void ABaseCharacter::Look(const FInputActionValue& Value)
{
	if (Controller)
	{
		// input is a Vector2D
		const FVector2D LookAxisVector = Value.Get<FVector2D>();
		
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ABaseCharacter::UseObject()
{
	if (Controller)
	{
		FHitResult Hit;
		const FVector StartLocation = GetFollowCamera()->GetComponentLocation();
		const FVector EndLocation = StartLocation + GetFollowCamera()->GetForwardVector() * (UseDistance + CameraBoom->TargetArmLength);
		if (GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, TraceChannel))
		{
			if(Hit.GetActor()->Implements<UUsable>())
			{
				IUsable::Execute_Use(Hit.GetActor(), this);
			}
		}
		// DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 3.0f, 0, 2.0f);
	}
}

void ABaseCharacter::ZoomCamera(const FInputActionValue& Value)
{
	if (Controller)
	{
		// const float ScrollValue = Value.Get<float>();
		//
		// // raycast and check hit objects
		// const float NewCameraZoom =  FMath::Clamp(CameraBoom->TargetArmLength + ScrollValue * CameraZoomMultiplier, MinCameraZoom, MaxCameraZoom);
		// CameraBoom->TargetArmLength = NewCameraZoom;

		PlayerCameraManager->ZoomCamera(Value.Get<float>());
	}
}

