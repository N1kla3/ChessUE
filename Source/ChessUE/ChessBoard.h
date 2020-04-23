// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoardCell.h"

#include "GameFramework/Actor.h"

#include "ChessBoard.generated.h"


UCLASS()
class CHESSUE_API AChessBoard : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChessBoard();
	
private:

	UPROPERTY(EditAnywhere, Category="Proprties")
	int32 ROWS;

	UPROPERTY(EditAnywhere, Category="Proporties")
	int32 COLUMNS;

	UPROPERTY(EditAnywhere, Category="Proporties")
	float Space;

	FBoardLocation WKingLocation;
	FBoardLocation BKingLocation;

	FBoardLocation WhoBeatWhiteKing;
	FBoardLocation WhoBeatBlackKing;

	bool bIsCheckToWhite;
	bool bIsCheckToBlack;

	TArray<FBoardLocation> FigureMoves;
	TArray<FBoardLocation> FigsLocation;
	
	UPROPERTY()
	USceneComponent* URoot;
	
	UPROPERTY()
	TArray<ABoardCell*> cells;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool CheckEverything(FBoardLocation MoveToLocation);
	
private:
	bool CheckForCheck();
	bool CheckForMate();
	TArray<FBoardLocation>& GetBlockCellsForLoc(TArray<FBoardLocation> AllMoves);
	TArray<FBoardLocation>& GetAllBlockCells();
	
	void SpawnCells();

	void SpawnOnePlayerFigures();

};
