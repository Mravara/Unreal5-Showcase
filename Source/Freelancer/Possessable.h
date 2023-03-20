// Copyrighted by Binx Games.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Possessable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPossessable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FREELANCER_API IPossessable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnPossess() = 0;
	virtual void OnUnPossess() = 0;
};
