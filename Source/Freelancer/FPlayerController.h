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

public:
	bool PossesPawn(APawn* Pawn);

private:
	UPROPERTY()
	APawn* PossessedPawn;
};
