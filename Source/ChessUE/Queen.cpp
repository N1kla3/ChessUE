// Fill out your copyright notice in the Description page of Project Settings.


#include "Queen.h"

AQueen::AQueen()
{
	const TCHAR* pathToModel = L"/Game/Shape_Cone.Shape_Cone";
	Init(pathToModel);
}

bool AQueen::CanMoveToLocation(FBoardLocation cell)
{
	return true;
}
