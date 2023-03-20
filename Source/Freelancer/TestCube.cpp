// Copyrighted by Binx Games.


#include "TestCube.h"

// Sets default values
ATestCube::ATestCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CubeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	AddOwnedComponent(CubeMeshComponent);
}

// Called when the game starts or when spawned
void ATestCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestCube::Use(APawn* Pawn)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Using Cube!"));
	CubeMeshComponent->AddImpulse(FVector::UpVector * 200000.f);
}




