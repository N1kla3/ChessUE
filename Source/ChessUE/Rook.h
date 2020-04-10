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

	virtual bool CanMoveToLocation(FBoardLocation)override;

};
