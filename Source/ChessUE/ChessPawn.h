// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessPiece.h"
#include "ChessPawn.generated.h"

/**
 * 
 */
UCLASS()
class CHESSUE_API AChessPawn : public AChessPiece
{
	GENERATED_BODY()

public:
	AChessPawn();
	virtual TArray<FBoardLocation>& GetAllMoves() override;
	
	virtual bool CanMoveToLocation(FBoardLocation cell) override;

	virtual TArray<FBoardLocation>& TryForEnemyKing(FBoardLocation KingLocation) override;

	virtual TArray<FBoardLocation>& GetCorrectMoves(TArray<FBoardLocation>& blockCells) override;

	bool IsFirstMove();

	int8 GetCurrentMoveNumber()const;
	void IncrementCurrentMoveNumber();

	void CheckEnPassant(const bool LeftToPawn, const bool RightToPawn);
	bool IsPromotionTime(const FBoardLocation LocationToMove)const;
private:
	bool bIsFirstMove;

	void AllMovesWithoutColor(int8 Navigation);
	
	int8 CurrentMoveNumber;
};
