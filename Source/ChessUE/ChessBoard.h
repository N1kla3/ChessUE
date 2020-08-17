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

	TArray<FBoardLocation> WhoBeatKing;

	bool bIsCheckToWhite;
	bool bIsCheckToBlack;

	TArray<FBoardLocation> FigureMoves;
	TArray<FLocWithColor> FigsLocation;
	TArray<FLocWithColor> BlockedForFigure;

	UPROPERTY()
	AChessPiece* ChosenPiece;
	
	UPROPERTY()
	USceneComponent* URoot;
	
	UPROPERTY()
	TArray<ABoardCell*> cells;

	TMultiMap<FBoardLocation, TArray<FBoardLocation>> PossibleChecks;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool CheckEverything(FBoardLocation MoveToLocation);
	/**
	 * write to FigureMoves only possible moves(finish calculation) of figure
	 */
	void SetChosenPiece(AChessPiece* Piece);
	void HighlightCells();
	void CreateFigureFromPawn(const FBoardLocation Location);
	void EmptyEnPass(FigureColor Color);
	void SetEnPass(FBoardLocation Location, FigureColor Color);
private:
	void CheckForCheck(TEnumAsByte<FigureColor> Color);
	bool CheckForMate();
	TArray<FLocWithColor>& GetBlockCellsForLoc(TArray<FBoardLocation> AllMoves);
	TArray<FLocWithColor>& GetAllBlockCells();

	void CanBeatKing(TArray<FBoardLocation>& EnemyFigMoves, FBoardLocation Location, TEnumAsByte<FigureColor> Side);
	bool IsInDefendersOfKing();
	void WhenDefender();
	void WhenCheck();
	void MakeMovesNoCheck();
	
	void SpawnCells();
	void ClearCell(const FBoardLocation Location);
	
	void SpawnBlackFigures();
	void SpawnWhiteFigures();

	FBoardLocation HandleChessPawn();
	
	FBoardLocation WhiteEnPassant;
	FBoardLocation BlackEnPassant;

	
};
