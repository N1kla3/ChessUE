// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessPiece.h"
#include "Rook.generated.h"

/**
 * 
 */
UCLASS()
class CHESSUE_API ARook : public AChessPiece
{
	GENERATED_BODY()

public:
	ARook();
	virtual TArray<FBoardLocation>& TryForEnemyKing(FBoardLocation KingLocation)override;
	
	virtual bool CanMoveToLocation(FBoardLocation)override;

	virtual TArray<FBoardLocation>& GetAllMoves()override;

	virtual TArray<FBoardLocation>& GetCorrectMoves(TArray<FLocWithColor>& blockCells)override;

	bool IsMoved(){return bIsMoved;}
	void Moved();
private:
	bool bIsMoved;
};
