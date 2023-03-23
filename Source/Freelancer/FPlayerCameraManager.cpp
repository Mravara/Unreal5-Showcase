// Copyrighted by Binx Games.


#include "FPlayerCameraManager.h"

#include "MathUtil.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values for this component's properties
UFPlayerCameraManager::UFPlayerCameraManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//
}


// Called when the game starts
void UFPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	TargetZoom = DefaultZoom;
}

void UFPlayerCameraManager::Init(UCameraComponent* sFollowCamera, USpringArmComponent* sCameraBoom)
{
	FollowCamera = sFollowCamera;
	CameraBoom = sCameraBoom;
}

// Called every frame
void UFPlayerCameraManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsUpdatingCameraZoom)
	{
		UpdateCameraZoom(DeltaTime);
	}

	if (IsUpdatingCameraPosition)
	{
		UpdateCameraShoulderPosition(DeltaTime);
	}
}

void UFPlayerCameraManager::ZoomCamera(float Direction)
{
	StartingZoom = CameraBoom->TargetArmLength;
	
	TargetZoom = FMathf::Clamp(TargetZoom + ZoomStep * Direction, MinZoom, MaxZoom);

	CurrentZoomDuration = 0.f;
	
	IsUpdatingCameraZoom = true;
}

void UFPlayerCameraManager::UpdateCameraZoom(const float DeltaTime)
{
	const float NormalizedTime = CurrentZoomDuration / ZoomDuration;

	if (NormalizedTime < 1.f)
	{
		const float CurvedTime = ZoomCurve->GetFloatValue(NormalizedTime);

		const float NewZoom = FMath::Lerp(StartingZoom, TargetZoom, CurvedTime);

		CameraBoom->TargetArmLength = NewZoom;
		
		CurrentZoomDuration += DeltaTime;
	}
	else
	{
		CameraBoom->TargetArmLength = TargetZoom;
		IsUpdatingCameraZoom = false;
	}
}

void UFPlayerCameraManager::SwitchShoulder()
{
	StartingCameraShoulderPosition = FollowCamera->GetRelativeLocation();
	
	CameraTargetShoulderPosition = CameraTargetShoulderPosition * -1.f;

	CurrentCameraTransitionDuration = 0.f;
	
	IsUpdatingCameraPosition = true;
}

void UFPlayerCameraManager::UpdateCameraShoulderPosition(const float DeltaTime)
{
	float NormalizedTime = CurrentCameraTransitionDuration / CameraTransitionDuration;

	if (NormalizedTime < 1.f)
	{
		const float CurvedTime = TransitionCurve->GetFloatValue(NormalizedTime);

		const FVector NewPosition = FMath::Lerp(StartingCameraShoulderPosition, CameraTargetShoulderPosition, CurvedTime);

		FollowCamera->SetRelativeLocation(NewPosition);
		
		CurrentCameraTransitionDuration += DeltaTime;
	}
	else
	{
		FollowCamera->SetRelativeLocation(CameraTargetShoulderPosition);
		IsUpdatingCameraPosition = false;
	}
}

