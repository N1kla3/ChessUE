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

	AKing();

	virtual bool CanMoveToLocation(FBoardLocation cell) override;
};
