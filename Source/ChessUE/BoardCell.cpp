// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardCell.h"

// Sets default values
ABoardCell::ABoardCell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoardCell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoardCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

