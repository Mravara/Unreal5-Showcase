// Copyrighted by Binx Games.


#include "FPlayerController.h"

#include "Possessable.h"

AFPlayerController::AFPlayerController()
{
}

void AFPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (IPossessable* PossessableInterface = Cast<IPossessable>(InPawn))
	{
		PossessableInterface->OnPossess();
		PossessedPawn = InPawn;
	}
}

void AFPlayerController::OnUnPossess()
{
	Super::OnUnPossess();

	if (IPossessable* PossessableInterface = Cast<IPossessable>(PossessedPawn))
	{
		PossessableInterface->OnUnPossess();
		PossessedPawn = nullptr;
	}
}
