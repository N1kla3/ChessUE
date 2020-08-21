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

	const int32 ROWS = 8;

	const int32 COLUMNS = 8;
	const float Space = 100.0;

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
	AChessPiece* CreateFigureFromPawn(const FBoardLocation Location);
	void EmptyEnPass(FigureColor Color);
	void SetEnPass(FBoardLocation Location, FigureColor Color);
	FBoardLocation GetEnPass(FigureColor Color)const;
	void DoShortCastling(FBoardLocation KingLocation);
	void DoLongCastling(FBoardLocation KingLocation);
	void ClearCell(const FBoardLocation Location);
	ABoardCell* FindCell(FBoardLocation Location);
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
	
	void SpawnBlackFigures();
	void SpawnWhiteFigures();

	void CheckShortCastling();
	void CheckLongCastling();

	/**
	 * Swaps from Second to first
	 */
	void SwapCellPieces(ABoardCell& First, ABoardCell& Second);

	bool CheckMovesForCheck(TArray<FBoardLocation>& Moves, FigureColor MoverColor);
	bool CheckOrNot(TArray<FBoardLocation>& DangerMoves);
	FBoardLocation HandleChessPawn();
	
	FBoardLocation WhiteEnPassant;
	FBoardLocation BlackEnPassant;

	AChessPiece* FindPiece(const FBoardLocation PieceLocation);
};
