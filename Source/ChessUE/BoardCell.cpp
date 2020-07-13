// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardCell.h"
#include "ConstructorHelpers.h"

#include "Components/StaticMeshComponent.h"


// Sets default values
ABoardCell::ABoardCell()
{
	PrimaryActorTick.bCanEverTick = true;
	InitMesh();
	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("Material'/Game/M_Tech_Hex_Tile.M_Tech_Hex_Tile'"));
	if (Material.Succeeded())
	{
		M_White = UMaterialInstanceDynamic::Create(Material.Object, Material.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial>Material1(TEXT("Material'/Game/M_Wood_Pine.M_Wood_Pine'"));
	if (Material1.Succeeded())
	{
		M_Black = UMaterialInstanceDynamic::Create(Material1.Object, Material1.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial>Material2(TEXT("Material'/Game/M_Ground_Moss.M_Ground_Moss'"));
	if (Material2.Succeeded())
	{
		M_Green = UMaterialInstanceDynamic::Create(Material2.Object, Material2.Object);
	}
}

void ABoardCell::InitColor(TEnumAsByte<FigureColor> Color)
{
	this->Color = Color;
	Color == White ? UCellMesh->SetMaterial(0, M_White):UCellMesh->SetMaterial(0, M_Black);	
}

void ABoardCell::SetBoardLocation(FBoardLocation newLocation)
{
	Xcoord = newLocation.Key;
	Ycoord = newLocation.Value;
}

void ABoardCell::SetPiece(AChessPiece *piece, TEnumAsByte<FigureColor> Color)
{
	this->piece = piece;
	this->piece->SetColor(Color);
	this->piece->SetActorLocation(GetActorLocation() + FVector(0.f, 0.f, 100.f));
	this->piece->SetBoardLocation(GetBoardLocation());
}

AChessPiece* ABoardCell::GetPiece()
{
	return piece ? piece : nullptr;
}

void ABoardCell::DestroyPiece()
{
	if (piece)
	{
		piece->Destroy();
	}
}

FBoardLocation ABoardCell::GetBoardLocation()
{
	return FBoardLocation(Xcoord, Ycoord);
}

void ABoardCell::SwapBetweenColors()
{
	if(IsColorChanger)
	{
		UCellMesh->SetMaterial(0, M_Green);
		IsColorChanger = false;
	}else
	{
		Color == White ? UCellMesh->SetMaterial(0, M_White):UCellMesh->SetMaterial(0, M_Black);
		IsColorChanger = true;
	}
}


void ABoardCell::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABoardCell::InitMesh()
{
	const TCHAR* PathToModel = TEXT("/Game/Shape_Cube.Shape_Cube");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> VisualAsset(PathToModel);

	URoot = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = URoot;

	UCellMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	if (VisualAsset.Succeeded())
	{
		UCellMesh->SetStaticMesh(VisualAsset.Object);
	}
	UCellMesh->SetupAttachment(RootComponent);
	IsColorChanger = false;
}

// Called every frame
void ABoardCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

