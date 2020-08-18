// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessPiece.h"
#include "King.generated.h"

/**
 * 
 */
UCLASS()
class CHESSUE_API AKing : public AChessPiece
{
	GENERATED_BODY()

public:
	AKing();
	virtual TArray<FBoardLocation>& GetAllMoves() override;
	
	virtual bool CanMoveToLocation(FBoardLocation cell) override;

	virtual TArray<FBoardLocation>& TryForEnemyKing(FBoardLocation KingLocation) override;

	virtual  TArray<FBoardLocation>& GetCorrectMoves(TArray<FLocWithColor>& blockCells) override;

	FBoardLocation AddShortCastling(bool IsPossible);
	FBoardLocation AddLongCastling(bool IsPossible);

	bool IsMoved(){return bNotMoved;}
	void Moved();
private:
	bool bNotMoved;
};
