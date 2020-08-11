// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bishop.h"
#include "Queen.generated.h"

/**
 * 
 */
UCLASS()
class CHESSUE_API AQueen : public ABishop
{
	GENERATED_BODY()

public:
	AQueen();
	virtual TArray<FBoardLocation>& TryForEnemyKing(FBoardLocation KingLocation) override;

	virtual bool CanMoveToLocation(FBoardLocation cell) override;

	virtual TArray<FBoardLocation>& GetAllMoves() override;

	virtual TArray<FBoardLocation>& GetCorrectMoves(TArray<FLocWithColor>& blockCells) override;
private:
	void RookKingTrier(FBoardLocation KingLocation);	
};
