// Fill out your copyright notice in the Description page of Project Settings.


#include "Bishop.h"
#include "Components/StaticMeshComponent.h"

ABishop::ABishop()
	:AChessPiece()
{
	const TCHAR* pathToModel = TEXT("/Game/Shape_Cone.Shape_Cone");
	Init(pathToModel);
}

bool ABishop::CanMoveToLocation(FBoardLocation cell)
{
	return true;
}

TArray<FBoardLocation>& ABishop::GetAllMoves()
{
	AllMoves.Empty();
	
	for(size_t i = MINlocation; i <= MAXlocation; ++i)
	{
		if(i == XBoardCoord)continue;
		if(IsOnBoard(i, YBoardCoord - i))
		{
			AllMoves.Emplace(i, YBoardCoord - i);
		}
		if(IsOnBoard(i, YBoardCoord + i))
		{
			AllMoves.Emplace(i, YBoardCoord + i);
		}
	}
	return AllMoves;
}

TArray<FBoardLocation>& ABishop::GetCorrectMoves(TArray<FBoardLocation>& blockCells)
{
	TArray<FBoardLocation> temp;

	bool oneSide = true, secSide = true;
	
	for(size_t i = XBoardCoord + 1; i <= MAXlocation; i++)
	{
		if(oneSide)
		{
			for(auto k : blockCells)
			{
				if(k.Key == i && k.Value == YBoardCoord - i)
				{
					oneSide = false;
				}
			}
			if (IsOnBoard(i, YBoardCoord - i) && oneSide)
			{
				temp.Emplace(i, YBoardCoord - i);
			}
		}
		if(secSide)
		{
			for (auto k : blockCells)
			{
				if (k.Key == i && k.Value == YBoardCoord + i)
				{
					secSide = false;
				}
			}
			if (IsOnBoard(i, YBoardCoord + i) && secSide)
			{
				temp.Emplace(i, YBoardCoord + i);
			}
		}
	}
	oneSide = true, secSide = true;

	for (size_t i = XBoardCoord - 1; i > 0 ; i--)
	{
		if (oneSide)
		{
			for (auto k : blockCells)
			{
				if (k.Key == i && k.Value == YBoardCoord - i)
				{
					oneSide = false;
				}
			}
			if (IsOnBoard(i, YBoardCoord - i) && oneSide)
			{
				temp.Emplace(i, YBoardCoord - i);
			}
		}
		if (secSide)
		{
			for (auto k : blockCells)
			{
				if (k.Key == i && k.Value == YBoardCoord + i)
				{
					secSide = false;
				}
			}
			if (IsOnBoard(i, YBoardCoord + i) && secSide)
			{
				temp.Emplace(i, YBoardCoord + i);
			}
		}
	}
	AllMoves = temp;
	
	return AllMoves;
}
