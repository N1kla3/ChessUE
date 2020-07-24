// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessPiece.h"
#include "Knight.generated.h"

/**
 * 
 */
UCLASS()
class CHESSUE_API AKnight : public AChessPiece
{
	GENERATED_BODY()

public:
	AKnight();
	virtual TArray<FBoardLocation>& TryForEnemyKing(FBoardLocation KingLocation) override;
	
	virtual bool CanMoveToLocation(FBoardLocation cell) override;

	virtual TArray<FBoardLocation>& GetAllMoves() override;

	virtual TArray<FBoardLocation>& GetCorrectMoves(TArray<FBoardLocation>& blockCells) override;
};
