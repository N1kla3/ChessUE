// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessBoard.h"
#include "BoardCell.h"
#include "Engine/World.h"

// Sets default values
AChessBoard::AChessBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ROWS = 8;
	COLUMNS = 8;
	Space = 100.0;
}

// Called when the game starts or when spawned
void AChessBoard::BeginPlay()
{
	Super::BeginPlay();
	SpawnCells();
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
			ABoardCell* temp = GetWorld()->SpawnActor<ABoardCell>(spawnLocation, rotation);
			temp->SetBoardLocation(FBoardLocation(i, k));
		}
	}
}

