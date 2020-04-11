// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessPiece.h"
#include "Queen.generated.h"

/**
 * 
 */
UCLASS()
class CHESSUE_API AQueen : public AChessPiece
{
	GENERATED_BODY()

public:
	AQueen();

	virtual bool CanMoveToLocation(FBoardLocation cell) override;
};
