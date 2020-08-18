// Fill out your copyright notice in the Description page of Project Settings.


#include "King.h"

AKing::AKing()
	: AChessPiece()
{
	const TCHAR* pathToModel = TEXT("/Game/Shape_Cone.Shape_Cone");
	Init(pathToModel);
	bNotMoved = false;
}

TArray<FBoardLocation>& AKing::GetAllMoves()
{
	AllMoves.Empty();
	if(IsOnBoard(XBoardCoord+1, YBoardCoord))AllMoves.Emplace(XBoardCoord+1, YBoardCoord);
	if(IsOnBoard(XBoardCoord-1, YBoardCoord))AllMoves.Emplace(XBoardCoord-1, YBoardCoord);
	if(IsOnBoard(XBoardCoord+1, YBoardCoord+1))AllMoves.Emplace(XBoardCoord+1, YBoardCoord+1);
	if(IsOnBoard(XBoardCoord, YBoardCoord+1))AllMoves.Emplace(XBoardCoord, YBoardCoord+1);
	if(IsOnBoard(XBoardCoord-1, YBoardCoord+1))AllMoves.Emplace(XBoardCoord-1, YBoardCoord+1);
	if(IsOnBoard(XBoardCoord+1, YBoardCoord-1))AllMoves.Emplace(XBoardCoord+1, YBoardCoord-1);
	if(IsOnBoard(XBoardCoord, YBoardCoord-1))AllMoves.Emplace(XBoardCoord, YBoardCoord-1);
	if(IsOnBoard(XBoardCoord-1, YBoardCoord-1))AllMoves.Emplace(XBoardCoord-1, YBoardCoord-1);
	return AllMoves;
}

bool AKing::CanMoveToLocation(FBoardLocation cell)
{
	return true;
}

TArray<FBoardLocation>& AKing::TryForEnemyKing(FBoardLocation KingLocation)
{
	KingTrier.Empty();
	return KingTrier;
}

TArray<FBoardLocation>& AKing::GetCorrectMoves(TArray<FLocWithColor>& blockCells)
{
	auto Temp = AllMoves;
	AllMoves.Empty();
	for(auto Move : Temp)
	{
		bool TimeTo = false;
		for(auto Block : blockCells)
		{
			if(Move == Block.Key && !IsEnemy(Block.Value))
			{
				TimeTo = true;
				break;
			}
		}
		if(!TimeTo)AllMoves.Add(Move);
	}
	return AllMoves;
}

FBoardLocation AKing::AddShortCastling(const bool IsPossible)
{
	if(IsPossible)
	{
		bool IsNotBlocked = false;
		for(auto Move : AllMoves)
		{
			if(Move == MakeTuple(XBoardCoord+1, YBoardCoord))
			{
				IsNotBlocked = true;
				break;
			}
		}
		if(IsNotBlocked)
		{
			AllMoves.Emplace(XBoardCoord+2, YBoardCoord);
			return MakeTuple(XBoardCoord+2, YBoardCoord);
		}
	}
	return MakeTuple(0,0);
}

FBoardLocation AKing::AddLongCastling(const bool IsPossible)
{
	if(IsPossible)
	{
		bool IsNotBlocked = false;
		for(auto Move : AllMoves)
		{
			if(Move == MakeTuple(XBoardCoord-1, YBoardCoord))
			{
				IsNotBlocked = true;
				break;
			}
		}
		if(IsNotBlocked)
		{
			AllMoves.Emplace(XBoardCoord-2, YBoardCoord);
			return MakeTuple(XBoardCoord-2, YBoardCoord);
		}
	}
	return MakeTuple(0,0);
}

void AKing::Moved()
{
	if(!bNotMoved)
		bNotMoved = true;
}
