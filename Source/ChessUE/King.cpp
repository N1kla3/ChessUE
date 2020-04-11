// Fill out your copyright notice in the Description page of Project Settings.


#include "King.h"

AKing::AKing()
	: AChessPiece()
{
	const TCHAR* pathToModel = L"/Game/Shape_Cone.Shape_Cone";
	Init(pathToModel);
}

bool AKing::CanMoveToLocation(FBoardLocation cell)
{
	return true;
}
