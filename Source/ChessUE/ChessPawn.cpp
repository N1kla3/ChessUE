// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPawn.h"

AChessPawn::AChessPawn()
	: AChessPiece()
{
	const TCHAR* pathToModel = TEXT("/Game/Shape_Cone.Shape_Cone");
	Init(pathToModel);
}

bool AChessPawn::CanMoveToLocation(FBoardLocation cell)
{
	return true;
}
