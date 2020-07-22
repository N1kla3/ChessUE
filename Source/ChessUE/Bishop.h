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
	virtual TArray<FBoardLocation>& TryForEnemyKing(FBoardLocation KingLocation)override;
	
	virtual bool CanMoveToLocation(FBoardLocation cell) override;

	virtual TArray<FBoardLocation>& GetAllMoves() override;

	virtual TArray<FBoardLocation>& GetCorrectMoves(TArray<FBoardLocation>& blockCells) override;
private:
	void GoDiagonal(const int8 Index, const int8 Diff, bool Side = true);
	bool GoThrowDiagonal(const int8 Index, bool Side, TArray<FBoardLocation>& BlockCells, const int8 Diff);
};
