// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnBoard.h"
#include "Engine/World.h"
#include "Bishop.h"

// Sets default values
ASpawnBoard::ASpawnBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*URoot->CreateDefaultSubobject<USceneComponent>(TEXT("scene"));
	RootComponent = URoot;*/
	
}

void ASpawnBoard::SpawnFigures()
{
	//tesst
	FVector vec1(100.f, 0.f, 0.f);
	FVector vec2(300.f, 0.f, 0.f);
	FVector vec3(500.f, 0.f, 0.f);
	FRotator rot(0.f, 0.f, 0.f);
	GetWorld()->SpawnActor<ABishop>(GetActorLocation(), rot);
	GetWorld()->SpawnActor<ABishop>(vec2, rot);
	GetWorld()->SpawnActor<ABishop>(vec3, rot);
}


// Called when the game starts or when spawned
void ASpawnBoard::BeginPlay()
{
	Super::BeginPlay();
	SpawnFigures();
}

// Called every frame
void ASpawnBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

