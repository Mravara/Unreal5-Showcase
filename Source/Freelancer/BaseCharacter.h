// Copyrighted by Binx Games.

#pragma once

#include "CoreMinimal.h"
#include "FPlayerCameraManager.h"
#include "Possessable.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

struct FInputActionValue;

UCLASS()
class FREELANCER_API ABaseCharacter : public ACharacter, public IPossessable
{
	GENERATED_BODY()

	// Camera boom positioning the camera behind the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	// Follow camera 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

	// Follow camera 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UFPlayerCameraManager> PlayerCameraManager;
	
	// MappingContext 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> MappingContext;

	// Jump Input Action 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	// Move Input Action 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	// Look Input Action 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	// Use Input Action 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> UseAction;

	// Zoom Input Action 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> CameraZoomAction;

	// Switch Shoulder Input Action 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> CameraSwitchShoulderAction;

	// Use Trace Channel
	UPROPERTY(EditAnywhere, Category = "Use")
	TEnumAsByte<ECollisionChannel> TraceChannel;

public:
	// Sets default values for this character's properties
	ABaseCharacter(const FObjectInitializer& OI);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Returns CameraBoom subobject
	FORCEINLINE TObjectPtr<USpringArmComponent> GetCameraBoom() const { return CameraBoom; }

	// Returns FollowCamera subobject
	FORCEINLINE TObjectPtr<UCameraComponent> GetFollowCamera() const { return FollowCamera; }

	// Called when pawn gets possessed
	virtual void OnPossess() override;

	// Called when pawn gets unpossessed
	virtual void OnUnPossess() override;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called for movement input
	void Move(const FInputActionValue& Value);

	// Called for looking input
	void Look(const FInputActionValue& Value);

	// Called for using input
	void UseObject();

	// Called for camera zoom input
	void ZoomCamera(const FInputActionValue& Value);

	// Called for camera shoulder switch
	void CameraSwitchShoulder();
	

public:	
	// Use Trace Distance
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Use")
	float UseDistance = 500.f;

	
private:
	void SetupInput();
	void RemoveInput();

};
