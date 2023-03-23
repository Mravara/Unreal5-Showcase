// Copyrighted by Binx Games.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPlayerCameraManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FREELANCER_API UFPlayerCameraManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFPlayerCameraManager();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// Init
	void Init(class UCameraComponent* FollowCamera, class USpringArmComponent* CameraBoom);
	
	// Called when initiating camera zoom
	void ZoomCamera(float Direction);

	// Called when switching shoulders for the camera
	void RepositionCamera();
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:
	
	// Camera boom
	UPROPERTY()
	TObjectPtr<USpringArmComponent> CameraBoom;

	// Follow camera 
	UPROPERTY()
	TObjectPtr<UCameraComponent> FollowCamera;
	
	// Zoom
	UPROPERTY()
	float StartingZoom;

	UPROPERTY()
	float TargetZoom;

	UPROPERTY(EditAnywhere, Category = "Camera Manager")
	float ZoomDuration = 1.f;

	UPROPERTY()
	float CurrentZoomDuration;

	UPROPERTY()
	bool IsUpdatingCameraZoom;

	UPROPERTY(EditAnywhere, Category = "Camera Manager")
	float DefaultZoom = 400.f;

	UPROPERTY(EditAnywhere, Category = "Camera Manager")
	float MinZoom = 300.f;

	UPROPERTY(EditAnywhere, Category = "Camera Manager")
	float MaxZoom = 700.f;
	
	UPROPERTY(EditAnywhere, Category = "Camera Manager")
	float ZoomStep = 50.f;

	UPROPERTY(EditAnywhere, Category = "Camera Manager")
	UCurveFloat* ZoomCurve;
	
	
	// Reposition properties
	UPROPERTY(EditAnywhere, Category = "Camera Manager")
	FVector CameraTargetShoulderPosition = FVector(0.f, 50.f, 0.f);

	UPROPERTY()
	FVector StartingCameraShoulderPosition;

	UPROPERTY()
	bool IsCameraOnRightSide;

	UPROPERTY(EditAnywhere, Category = "Camera Manager")
	float CameraTransitionDuration = 1.f;

	UPROPERTY()
	float CurrentCameraTransitionDuration;

	UPROPERTY()
	bool IsUpdatingCameraPosition;

	UPROPERTY(EditAnywhere, Category = "Camera Manager")
	UCurveFloat* TransitionCurve;
	
	
	// Called every frame while updating camera zoom
	void UpdateCameraZoom(const float DeltaTime);

	// Called every frame while updating camera position
	void UpdateCameraPosition(const float DeltaTime);

	
};

