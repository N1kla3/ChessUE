// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "ChessUEGameModeBase.h"

AChessUEGameModeBase::AChessUEGameModeBase()
{
	DefaultPawnClass = AGamePawn::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
}
