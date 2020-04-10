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

	virtual bool CanMoveToLocation(FBoardLocation cell) override;
};
