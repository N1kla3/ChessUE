// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPawn.h"

AChessPawn::AChessPawn()
	: AChessPiece()
{
	const TCHAR* pathToModel = TEXT("/Game/Shape_Cone.Shape_Cone");
	Init(pathToModel);
	bIsFirstMove = false;
}

TArray<FBoardLocation>& AChessPawn::GetAllMoves()
{
	AllMoves.Empty();
	if(Color == White)
	{
		AllMovesWithoutColor(1);
	}
	else
	{
		AllMovesWithoutColor(-1);
	}
}

bool AChessPawn::CanMoveToLocation(FBoardLocation cell)
{
	return true;
}

bool AChessPawn::IsFirstMove()
{
	return bIsFirstMove;
}

void AChessPawn::AllMovesWithoutColor(const int8 Navigation)
{
	for(int8 i = -1; i <= 1; i++)
	{
		auto temp = Navigation;
		if(i == 0)
		{
			temp += Navigation;
		}	
		if(IsOnBoard(XBoardCoord+i, YBoardCoord))AllMoves.Emplace(XBoardCoord+i, YBoardCoord);
		if(IsOnBoard(XBoardCoord+i, YBoardCoord+temp))
			AllMoves.Emplace(XBoardCoord+i, YBoardCoord+temp);
	}
}
