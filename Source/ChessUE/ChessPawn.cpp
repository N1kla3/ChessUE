// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPawn.h"

AChessPawn::AChessPawn()
	: AChessPiece()
{
	const TCHAR* pathToModel = TEXT("/Game/Shape_Cone.Shape_Cone");
	Init(pathToModel);
	bIsFirstMove = false;
	CurrentMoveNumber = 0;
}

TArray<FBoardLocation>& AChessPawn::GetAllMoves()
{
	AllMoves.Empty();
	if(Color == Black)
	{
		AllMovesWithoutColor(1);
	}
	else
	{
		AllMovesWithoutColor(-1);
	}
	return AllMoves;
}

bool AChessPawn::CanMoveToLocation(FBoardLocation cell)
{
	return true;
}

TArray<FBoardLocation>& AChessPawn::TryForEnemyKing(FBoardLocation KingLocation)
{
	KingTrier.Empty();
	if(Color == White)
	{
		if(IsOnBoard(XBoardCoord-1, YBoardCoord+1))KingTrier.Emplace(XBoardCoord-1, YBoardCoord+1);
		if(IsOnBoard(XBoardCoord-1, YBoardCoord+1))KingTrier.Emplace(XBoardCoord-1, YBoardCoord+1);
	}
	else
	{
		if(IsOnBoard(XBoardCoord-1, YBoardCoord-1))KingTrier.Emplace(XBoardCoord-1, YBoardCoord-1);
		if(IsOnBoard(XBoardCoord-1, YBoardCoord-1))KingTrier.Emplace(XBoardCoord-1, YBoardCoord-1);
	}
	return KingTrier;
}

TArray<FBoardLocation>& AChessPawn::GetCorrectMoves(TArray<FLocWithColor>& blockCells)
{
	auto Temp = AllMoves;
	AllMoves.Empty();
	for(auto BlockCell : blockCells)
	{
		if(BlockCell.Key.Key != XBoardCoord && IsEnemy(BlockCell.Value))
		{
			AllMoves.Add(BlockCell.Key);
		}
	}
	bool bHalfBlock = false;
	for(auto i : Temp)
	{
		if(i.Key == XBoardCoord)
		{
			for(auto k : blockCells)
			{
				if(i == k.Key)
				{
					bHalfBlock = true;
				}
			}
			if(!bHalfBlock)AllMoves.Add(i);
		}
	}
	return AllMoves;
}


bool AChessPawn::IsFirstMove()
{
	return bIsFirstMove;
}

void AChessPawn::AllMovesWithoutColor(const int8 Navigation)
{
	for(int8 i = -1; i <= 1; i++)
	{
		if(IsOnBoard(XBoardCoord+i, YBoardCoord+Navigation))AllMoves.Emplace(XBoardCoord+i, YBoardCoord+Navigation);
	}
	if(CurrentMoveNumber == 0)
	{
		if(IsOnBoard(XBoardCoord, YBoardCoord+2*Navigation))AllMoves.Emplace(XBoardCoord, YBoardCoord+2*Navigation);
	}
}

int8 AChessPawn::GetCurrentMoveNumber()const
{
	return CurrentMoveNumber;
}

void AChessPawn::IncrementCurrentMoveNumber()
{
	CurrentMoveNumber++;
}

void AChessPawn::CheckEnPassant(const bool LeftToPawn, const bool RightToPawn)
{
	if(LeftToPawn)
	{
		AllMoves.Emplace(XBoardCoord-1, YBoardCoord);
	}
	if(RightToPawn)
	{
		AllMoves.Emplace(XBoardCoord+1, YBoardCoord);
	}
}

bool AChessPawn::IsPromotionTime(const FBoardLocation LocationToMove)const
{
	if(Color == White && LocationToMove.Key == 1)
	{
		return true;
	}
	if(Color == Black && LocationToMove.Key == 8)
	{
		return true;
	}
	return false;
}
