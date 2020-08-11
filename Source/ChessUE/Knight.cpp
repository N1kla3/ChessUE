// Fill out your copyright notice in the Description page of Project Settings.


#include "Knight.h"

AKnight::AKnight()
	:AChessPiece()
{
	const TCHAR* pathToModel = TEXT("/Game/Shape_Cone.Shape_Cone");
	Init(pathToModel);
}

TArray<FBoardLocation>& AKnight::TryForEnemyKing(FBoardLocation KingLocation)
{
	KingTrier.Empty();
	bool IsOnKnightLocation = (abs(KingLocation.Key - XBoardCoord) == 2)
							&&(abs(KingLocation.Value - YBoardCoord) == 1);
	if(IsOnKnightLocation)
	{
		KingTrier.Add(KingLocation);
		return KingTrier;
	}
	IsOnKnightLocation = (abs(KingLocation.Key - XBoardCoord) == 1)
                            &&(abs(KingLocation.Value - YBoardCoord) == 2);
	if(IsOnKnightLocation)
	{
		KingTrier.Add(KingLocation);
		return KingTrier;
	}
	return KingTrier;
}

bool AKnight::CanMoveToLocation(FBoardLocation cell)
{
	return true;
}

TArray<FBoardLocation>& AKnight::GetAllMoves()
{
	AllMoves.Empty();
	for(int8 i = -2; i <= 2; i++)
	{
		if(i==0)continue;
		const int8 Shift = abs(i) == 2 ? 1 : 2;
		if(IsOnBoard(XBoardCoord+i, YBoardCoord-Shift))AllMoves.Emplace(XBoardCoord+i, YBoardCoord-Shift);
		if(IsOnBoard(XBoardCoord+i, YBoardCoord+Shift))AllMoves.Emplace(XBoardCoord+i, YBoardCoord+Shift);
	}
	return AllMoves;
}

TArray<FBoardLocation>& AKnight::GetCorrectMoves(TArray<FLocWithColor>& blockCells)
{
	auto Temp = AllMoves;
	AllMoves.Empty();
	for(auto move : Temp)
	{
		bool IsBlocked = false;
		for(auto blockCell : blockCells)
		{
			if(move == blockCell.Key && !IsEnemy(blockCell.Value))
			{
				IsBlocked = true;
			}
		}
		if(!IsBlocked)AllMoves.Add(move);
	}
	return AllMoves;
}
