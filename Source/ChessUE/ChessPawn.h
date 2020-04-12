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

	virtual bool CanMoveToLocation(FBoardLocation cell) override;
};
