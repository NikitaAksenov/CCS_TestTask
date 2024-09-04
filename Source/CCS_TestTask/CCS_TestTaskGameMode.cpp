// Copyright Epic Games, Inc. All Rights Reserved.

#include "CCS_TestTaskGameMode.h"
#include "CCS_TestTaskCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACCS_TestTaskGameMode::ACCS_TestTaskGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
