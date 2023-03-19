// Copyrighted by Binx Games.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IUsable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIUsable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FREELANCER_API IIUsable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Use() {}
};
