// Fill out your copyright notice in the Description page of Project Settings.


#include "Bishop.h"
#include "Components/StaticMeshComponent.h"

ABishop::ABishop()
	:AChessPiece()
{
	const TCHAR* pathToModel = L"/Game/Shape_Cone.Shape_Cone";
	Init(pathToModel);
}

bool ABishop::CanMoveToLocation(FBoardLocation cell)
{
	return true;
}
