// Fill out your copyright notice in the Description page of Project Settings.


#include "Rook.h"

#include <utility>

#include "Components/StaticMeshComponent.h"

ARook::ARook()
	: AChessPiece()
{
	const TCHAR* pathToModel = TEXT("/Game/Shape_Cone.Shape_Cone");
	Init(pathToModel);
}

TArray<FBoardLocation>& ARook::TryForEnemyKing(FBoardLocation KingLocation)
{
	KingTrier.Empty();
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
	return KingTrier;
}

bool ARook::CanMoveToLocation(FBoardLocation cell)
{
	return true;
}

TArray<FBoardLocation>& ARook::GetAllMoves()
{
	AllMoves.Empty();
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

TArray<FBoardLocation>& ARook::GetCorrectMoves(TArray<FBoardLocation>& blockCells)
{
	AllMoves.Empty();
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

bool ARook::GoThroughLine(const int8 X, const int8 Y, TArray<FBoardLocation>& BlockCells)
{
	if(IsOnBoard(X, Y))
	{
		bool IsInclude = true;
		for(auto cell : BlockCells)
		{
			if(cell == FBoardLocation(X, Y))
			{
				IsInclude = false;
				break;
			}
		}
		if(IsInclude)
		{
			AllMoves.Emplace(X, Y);
			return false;
		}
	}
	return true;
}

