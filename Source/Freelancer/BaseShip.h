// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Possessable.h"
#include "Usable.h"
#include "GameFramework/Pawn.h"
#include "BaseShip.generated.h"

UCLASS()
class FREELANCER_API ABaseShip : public APawn, public IUsable, public IPossessable
{
	GENERATED_BODY()

	// Static Mesh
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	// Camera boom positioning the camera behind the character 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// Follow camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	// MappingContext 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* MappingContext;

	// Jump Input Action 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FlyUpAction;

	// Jump Input Action 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FlyDownAction;

	// Move Input Action 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	// Look Input Action 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	// Use Input Action 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* UseAction;

	// Use Input Action 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* CameraZoomAction;

	// Zoom Multiplier
	UPROPERTY(EditAnywhere, Category = "Camera Zoom")
	float CameraZoomMultiplier = 10.f;

	// Min Camera Zoom
	UPROPERTY(EditAnywhere, Category = "Camera Zoom")
	float MinCameraZoom = 300.f;

	// Max Camera Zoom
	UPROPERTY(EditAnywhere, Category = "Camera Zoom")
	float MaxCameraZoom = 700.f;

public:
	// Sets default values for this pawn's properties
	ABaseShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when the object is used
	virtual void Use(APawn* Pawn) override;

	// Called when pawn gets possessed
	virtual void OnPossess() override;

	// Called when pawn gets unpossessed
	virtual void OnUnPossess() override;

private:
	// Driver - Unpossess will return the control to the driver
	UPROPERTY()
	APawn* Driver;

	// Gain altitude
	void FlyUp(const FInputActionValue& Value);

	// Lower altitude
	void FlyDown(const FInputActionValue& Value);

	// Move vehicle
	void Move(const FInputActionValue& Value);

	// Rotate camera around the vehicle
	void Look(const FInputActionValue& Value);

	// Zoom in and out
	void ZoomCamera(const FInputActionValue& Value);

	// Give Control Back
	void Possess(APawn* Pawn);

	// Give Control Back
	void Unpossess();

	// Setup Input
	void SetupInput();

	// Setup Input
	void RemoveInput();
};
