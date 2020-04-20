// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPiece.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"

// Sets default values
AChessPiece::AChessPiece()
{
	
}

// Called when the game starts or when spawned
void AChessPiece::BeginPlay()
{
	Super::BeginPlay();
	
}

void AChessPiece::Init(const TCHAR* pathToModel)
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> visualAsset(pathToModel);

	FigScene = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = FigScene;

	Figure = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("figure"));
	if (visualAsset.Succeeded())
	{
		Figure->SetStaticMesh(visualAsset.Object);
		Figure->SetCollisionProfileName(TEXT("ForFigures"));
	}
	Figure->SetupAttachment(RootComponent);
}

bool AChessPiece::IsOnBoard(int32 X, int32 Y)const
{
	if(X > MAXlocation && X < MINlocation)
	{
		return false;
	}
	if(Y > MAXlocation && Y < MINlocation)
	{
		return false;
	}
	return true;
}

bool AChessPiece::CanMoveToLocation(FBoardLocation cell)
{
	return true;
}

void AChessPiece::Highlight()
{	
	
}

FBoardLocation AChessPiece::GetBoardLocation()
{
	return FBoardLocation(XBoardCoord, YBoardCoord);
}

TArray<FBoardLocation>& AChessPiece::GetAllMoves()
{
	return AllMoves;
}

TArray<FBoardLocation>& AChessPiece::GetCorrectMoves(TArray<FBoardLocation>& blockCells)
{
	return AllMoves;
}

void AChessPiece::SetBoardLocation(FBoardLocation Location)
{
	XBoardCoord = Location.Key;
	YBoardCoord = Location.Value;
}

// Called every frame
void AChessPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

