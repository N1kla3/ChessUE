// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/BasicArray.h"
#include "ChessPiece.generated.h"
typedef TPair<int32, int32> FBoardLocation;

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

	
	TArray<FBoardLocation> AllMoves;
	

public:
	virtual bool CanMoveToLocation(FBoardLocation cell);

	void Highlight();

	FBoardLocation GetBoardLocation();

	virtual TArray<FBoardLocation>& GetAllMoves();
	virtual TArray<FBoardLocation>& GetCorrectMoves(TArray<FBoardLocation> &blockCells);
	
	void SetBoardLocation(FBoardLocation);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Init(const TCHAR* pathToModel);

	bool IsOnBoard(int32 X, int32 Y)const;
	
};
