// Fill out your copyright notice in the Description page of Project Settings.


#include "Knight.h"

AKnight::AKnight()
{
	const TCHAR* pathToModel = TEXT("/Game/Shape_Cone.Shape_Cone");
	Init(pathToModel);
}

bool AKnight::CanMoveToLocation(FBoardLocation cell)
{
	return true;
}
