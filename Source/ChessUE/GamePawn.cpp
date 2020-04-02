// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePawn.h"

#include "BoardCell.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"


AGamePawn::AGamePawn()
{
	bIsCLicked = false;
	PScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = PScene;

	PCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	PCamera->SetupAttachment(RootComponent);
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}


void AGamePawn::BeginPlay()
{
	Super::BeginPlay();
}


void AGamePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(CurrentChessPieceFocus)
	{
		CurrentChessPieceFocus->Highlight();
	}
	
}


void AGamePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("ClickChessPiece", EInputEvent::IE_Pressed, this, &AGamePawn::ClickChessPiece);
	PlayerInputComponent->BindAxis("MoveChessPiece", this, &AGamePawn::MoveChessPiece);
}

void AGamePawn::ClickChessPiece()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		FVector Start, Dir;
		PC->DeprojectMousePositionToWorld(Start, Dir);
		FVector End = Start + (Dir * 8000.0f);
		
		if (CurrentChessPieceFocus) 
		{
			FVector ceilLocation = TraceForCeil(Start, End);
			MoveToCeil(ceilLocation);
			CurrentChessPieceFocus = nullptr;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Moved"));
		}
		else
		{	
			TraceForChessPiece(Start, End);
		}
	}	
}

void AGamePawn::MoveChessPiece(float a)
{
	
	//method for moving figures on release
}

void AGamePawn::MoveToCeil(FVector cellLocation)
{
	CurrentChessPieceFocus->SetActorLocation(cellLocation+FVector(0.f, 0.f, 100.f));
}


void AGamePawn::TraceForChessPiece(const FVector& Start, const FVector& End)
{
	FHitResult FigureHit;
	GetWorld()->LineTraceSingleByChannel(FigureHit, Start, End, ECC_Visibility);

	if(FigureHit.Actor.IsValid())
	{
		AChessPiece* HitPiece = Cast<AChessPiece>(FigureHit.Actor.Get());

		if(CurrentChessPieceFocus != HitPiece)
		{
		
			CurrentChessPieceFocus = HitPiece;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("find new"));
			
		}
	}
}

FVector AGamePawn::TraceForCeil(const FVector& Start, const FVector& End)
{
	FHitResult CeilHit;
	GetWorld()->LineTraceSingleByChannel(CeilHit, Start, End, ECC_Visibility);

	if(CeilHit.Actor.IsValid())
	{
		ABoardCell* hitBlock = Cast<ABoardCell>(CeilHit.Actor.Get());

		CurrentChessPieceFocus->SetBoardLocation(hitBlock->GetBoardLocation());
		return hitBlock->GetActorLocation();
	}
	
	return FVector(-1.f, 0.f, 0.f);
}
