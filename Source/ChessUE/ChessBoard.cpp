// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessBoard.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "ChessPawn.h"

#include "Engine/World.h"

// Sets default values
AChessBoard::AChessBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ROWS = 8;
	COLUMNS = 8;
	Space = 100.0;

	URoot = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = URoot;
}

// Called when the game starts or when spawned
void AChessBoard::BeginPlay()
{
	Super::BeginPlay();
	SpawnCells();
	SpawnOnePlayerFigures();
}

// Called every frame
void AChessBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChessBoard::SpawnCells()
{
	FVector curActorLocation = GetActorLocation();
	
	for(int32 i = 1; i <= ROWS; i++)
	{
		for(int32 k = 1; k <= COLUMNS; k++)
		{
			FRotator rotation = FRotator(0.f, 0.f, 0.f);
			FVector spawnLocation = curActorLocation + FVector(Space*i, Space*k, 0.f);
            ABoardCell* cell = GetWorld()->SpawnActor<ABoardCell>(spawnLocation, rotation);
			cell->SetBoardLocation(FBoardLocation(i, k));
			cells.Add(cell);
		}
	}
}

void AChessBoard::SpawnOnePlayerFigures()
{
	FVector curActorLocation = GetActorLocation();
	FRotator rot(0.f, 0.f, 0.f);

	cells[0 * COLUMNS]->SetPiece(GetWorld()->SpawnActor<ARook>(curActorLocation, rot));
	cells[7 * COLUMNS]->SetPiece(GetWorld()->SpawnActor<ARook>(curActorLocation, rot));

	cells[1 * COLUMNS]->SetPiece(GetWorld()->SpawnActor<AKnight>(curActorLocation, rot));
	cells[6 * COLUMNS]->SetPiece(GetWorld()->SpawnActor<AKnight>(curActorLocation, rot));

	cells[2 * COLUMNS]->SetPiece(GetWorld()->SpawnActor<ABishop>(curActorLocation, rot));
	cells[5 * COLUMNS]->SetPiece(GetWorld()->SpawnActor<ABishop>(curActorLocation, rot));

	cells[3 * COLUMNS]->SetPiece(GetWorld()->SpawnActor<AKing>(curActorLocation, rot));
	cells[4 * COLUMNS]->SetPiece(GetWorld()->SpawnActor<AQueen>(curActorLocation, rot));

	for(int i = 0; i < ROWS; i++)
	{
		cells[i * COLUMNS + 1]->SetPiece(GetWorld()->SpawnActor<AChessPawn>(curActorLocation, rot));
	}
}

