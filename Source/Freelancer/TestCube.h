// Copyrighted by Binx Games.

#pragma once

#include "CoreMinimal.h"
#include "IUsable.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "TestCube.generated.h"

UCLASS()
class FREELANCER_API ATestCube : public AActor, public IIUsable
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	ATestCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxComponent;

	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the object is used
	virtual void Use() override;

};
