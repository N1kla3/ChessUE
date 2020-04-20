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

	virtual bool CanMoveToLocation(FBoardLocation cell) override;

	virtual TArray<FBoardLocation>& GetAllMoves() override;
};
