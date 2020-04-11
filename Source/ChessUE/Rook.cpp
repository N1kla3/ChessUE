// Fill out your copyright notice in the Description page of Project Settings.


#include "Rook.h"
#include "Components/StaticMeshComponent.h"

ARook::ARook()
	: AChessPiece()
{
	const TCHAR* pathToModel = L"/Game/Shape_Cone.Shape_Cone";
	Init(pathToModel);
}

bool ARook::CanMoveToLocation(FBoardLocation cell)
{
	return true;
}

