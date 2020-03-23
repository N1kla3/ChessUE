// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnBoard.h"

// Sets default values
ASpawnBoard::ASpawnBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnBoard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

