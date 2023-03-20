// Copyrighted by Binx Games.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FREELANCER_API AFPlayerController : public APlayerController
{
	GENERATED_BODY()

	AFPlayerController();

protected:
	void OnPossess(APawn* InPawn) override;
	void OnUnPossess() override;

private:
	UPROPERTY()
	APawn* PossessedPawn;
};
