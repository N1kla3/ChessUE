// Fill out your copyright notice in the Description page of Project Settings.


#include "Queen.h"

AQueen::AQueen()
	:ABishop(TEXT("/Game/Shape_Cone.Shape_Cone"))
{
}

TArray<FBoardLocation>& AQueen::TryForEnemyKing(FBoardLocation KingLocation)
{
	if(ABishop::TryForEnemyKing(KingLocation).IsValidIndex(0))
		return KingTrier;
	RookKingTrier(KingLocation);
	return KingTrier;
}

bool AQueen::CanMoveToLocation(FBoardLocation cell)
{
	return true;
}

TArray<FBoardLocation>& AQueen::GetAllMoves()
{
	ABishop::GetAllMoves();
	for(int8 x = 1; x <= MAXlocation; ++x)
	{
		if(x == XBoardCoord)continue;
		AllMoves.Emplace(x, YBoardCoord);
	}
	for(int8 y = 1; y <= MAXlocation; ++y)
	{
		if(y == YBoardCoord)continue;
		AllMoves.Emplace(XBoardCoord, y);
	}
	return AllMoves;
}

TArray<FBoardLocation>& AQueen::GetCorrectMoves(TArray<FBoardLocation>& blockCells)
{
	ABishop::GetCorrectMoves(blockCells);
	for(int8 i = XBoardCoord+1; i <= MAXlocation; ++i)
	{
		if(GoThroughLine(i, YBoardCoord, blockCells))break;
	}
	for(int8 i = XBoardCoord-1; i >= MINlocation; --i)
	{
		if(GoThroughLine(i, YBoardCoord, blockCells))break;
	}
	for(int8 i = YBoardCoord+1; i <= MAXlocation; ++i)
	{
		if(GoThroughLine(XBoardCoord, i, blockCells))break;
	}
	for(int8 i = YBoardCoord-1; i >= MINlocation; --i)
	{
		if(GoThroughLine(XBoardCoord, i, blockCells))break;
	}
	return AllMoves;
}

void AQueen::RookKingTrier(FBoardLocation KingLocation)
{
	if(KingLocation.Key == XBoardCoord)
	{
		const int8 shift = KingLocation.Value < YBoardCoord ? -1 : 1;
		for(int8 i = YBoardCoord+1; i != KingLocation.Value+shift; i += shift)
		{
			KingTrier.Emplace(XBoardCoord, i);
		}
	}
	else if(KingLocation.Value == YBoardCoord)
	{
		const int8 shift = KingLocation.Key < XBoardCoord ? -1 : 1;
		for(int8 i = XBoardCoord+1; i != KingLocation.Key; i += shift)
		{
			KingTrier.Emplace(i, YBoardCoord);
		}
	}
}