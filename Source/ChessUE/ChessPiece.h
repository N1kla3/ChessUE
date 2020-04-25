// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Map.h"
#include "ChessPiece.generated.h"
typedef TPair<int32, int32> FBoardLocation;

UENUM()
enum FigureColor
{
	White,
	Black
};

UCLASS(Abstract)
class CHESSUE_API AChessPiece : public AActor
{	GENERATED_BODY()

public:
	AChessPiece();
	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY()
	int32 XBoardCoord;

	UPROPERTY()
	int32 YBoardCoord;

	const int32 MINlocation = 1;
	const int32 MAXlocation = 8;

	UPROPERTY()
	USceneComponent* FigScene;
	
	UPROPERTY()
	UStaticMeshComponent* Figure;

	TEnumAsByte<FigureColor> Color;
	
	/**
	 * Array that keeps all possible moves of figure, independently of other figures locations
	 */
	TArray<FBoardLocation> AllMoves;
	

public:
	virtual bool CanMoveToLocation(FBoardLocation cell);

	void Highlight();

	FBoardLocation GetBoardLocation();
	void SetBoardLocation(FBoardLocation);

	/**
	 * \brief If it theoretically possible to beat a king, return a path from figure to enemy King
	 * \param KingLocation 
	 * \return that path
	 */
	virtual TArray<FBoardLocation>& TryForEnemyKing(FBoardLocation KingLocation);
	virtual TArray<FBoardLocation>& GetAllMoves();
	virtual TArray<FBoardLocation>& GetCorrectMoves(TArray<FBoardLocation> &blockCells);
	
	void SetColor(TEnumAsByte<FigureColor> Color);
	TEnumAsByte<FigureColor> GetColor() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Init(const TCHAR* pathToModel);

	bool IsOnBoard(int32 X, int32 Y)const;

};
