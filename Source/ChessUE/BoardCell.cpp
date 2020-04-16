// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardCell.h"
#include "ConstructorHelpers.h"

#include "Components/StaticMeshComponent.h"


// Sets default values
ABoardCell::ABoardCell()
{
	PrimaryActorTick.bCanEverTick = true;
	InitMesh();
}

void ABoardCell::SetBoardLocation(FBoardLocation newLocation)
{
	Xcoord = newLocation.Key;
	Ycoord = newLocation.Value;
}

void ABoardCell::SetPiece(AChessPiece *piece)
{
	this->piece = piece;

	this->piece->SetActorLocation(GetActorLocation() + FVector(0.f, 0.f, 100.f));
	this->piece->SetBoardLocation(GetBoardLocation());
}

FBoardLocation ABoardCell::GetBoardLocation()
{
	return FBoardLocation(Xcoord, Ycoord);
}


void ABoardCell::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABoardCell::InitMesh()
{
	const TCHAR* PathToModel = L"/Game/Shape_Cube.Shape_Cube";
	static ConstructorHelpers::FObjectFinder<UStaticMesh> VisualAsset(PathToModel);

	URoot = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = URoot;

	UCellMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	if (VisualAsset.Succeeded())
	{
		UCellMesh->SetStaticMesh(VisualAsset.Object);
	}
	UCellMesh->SetupAttachment(RootComponent);
}

// Called every frame
void ABoardCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

