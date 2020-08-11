// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessPiece.h"
#include "Bishop.generated.h"

/**
 * 
 */
UCLASS()
class CHESSUE_API ABishop : public AChessPiece
{
	GENERATED_BODY()
public:
	ABishop();
	explicit ABishop(const TCHAR* Path);
	virtual TArray<FBoardLocation>& TryForEnemyKing(FBoardLocation KingLocation)override;
	
	virtual bool CanMoveToLocation(FBoardLocation cell) override;

	virtual TArray<FBoardLocation>& GetAllMoves() override;

	virtual TArray<FBoardLocation>& GetCorrectMoves(TArray<FLocWithColor>& blockCells) override;
protected:
	void GoDiagonal(const int8 Index, const int8 Diff, bool Side = true);
	bool GoThrowDiagonal(const int8 Index, bool Side, TArray<FLocWithColor>& BlockCells, const int8 Diff);
};
