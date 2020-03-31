// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardCell.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"

// Sets default values
ABoardCell::ABoardCell()
{
	PrimaryActorTick.bCanEverTick = true;
	InitMesh();
}

ABoardCell::ABoardCell(int32 X, int32 Y)
	: Xcoord(X)
	, Ycoord(Y)
{
	InitMesh();
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

