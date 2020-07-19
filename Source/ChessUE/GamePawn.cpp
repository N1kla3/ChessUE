// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePawn.h"

#include "BoardCell.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerController.h"


AGamePawn::AGamePawn()
{
	bIsCLicked = false;
	PScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = PScene;

	PblackCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	PblackCamera->SetupAttachment(RootComponent);

	PwhiteCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("whiteCamera"));
	PwhiteCamera->SetupAttachment(RootComponent);
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	CurPlayerSide = White;
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
	if(!Board)
	{
		FindChessBoard();
	}
	
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		FVector Start, Dir;
		PC->DeprojectMousePositionToWorld(Start, Dir);
		FVector End = Start + (Dir * 8000.0f);
		
		if (CurrentChessPieceFocus) 
		{
			TraceForCeil(Start, End);
			HandleChessPiece();
		}
		else
		{	
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("try to find"));
			TraceForChessPiece(Start, End);
		}
	}	
}

void AGamePawn::MoveChessPiece(float a)
{
	
	//method for moving figures on release
}

void AGamePawn::MoveFigureToCeil()
{
	CurrentCellFocus->DestroyPiece();
	CurrentCellFocus->SetPiece(CurrentChessPieceFocus, CurrentChessPieceFocus->GetColor());
	CurrentChessPieceFocus = nullptr;
	CurrentCellFocus = nullptr;
	SwapPlayers();	
}

TArray<FBoardLocation>& AGamePawn::GetOccupiedLocations()
{
	return CurrFigureMoves;
}


void AGamePawn::TraceForChessPiece(const FVector& Start, const FVector& End)
{
	FHitResult FigureHit;
	GetWorld()->LineTraceSingleByChannel(FigureHit, Start, End, ECC_GameTraceChannel1);

	if(FigureHit.Actor.IsValid())
	{
		AChessPiece* HitPiece = Cast<AChessPiece>(FigureHit.Actor.Get());

		if(CurrentChessPieceFocus != HitPiece)
		{
			if(CurPlayerSide == HitPiece->GetColor())
			{
				CurrentChessPieceFocus = HitPiece;
				Board->SetChosenPiece(CurrentChessPieceFocus);
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("find new"));
			}else GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("another color"));
		}
	}
}

void AGamePawn::TraceForCeil(const FVector& Start, const FVector& End)
{
	FHitResult CeilHit;
	GetWorld()->LineTraceSingleByChannel(CeilHit, Start, End, ECC_Visibility);

	if(CeilHit.Actor.IsValid())
	{
		CurrentCellFocus = Cast<ABoardCell>(CeilHit.Actor.Get());
		if (CurrentCellFocus != nullptr) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("find new cell"));
		}
	}
}

void AGamePawn::FindChessBoard()
{
	for (TActorIterator<AChessBoard> Itr(GetWorld()); Itr; ++Itr) 
	{
		Board = Cast<AChessBoard>(*Itr);
		if(Board)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("find board"));
			return;
		}
	}
}

void AGamePawn::HandleChessPiece()
{
	if (CurrentCellFocus) {
		if(Board->CheckEverything(CurrentCellFocus->GetBoardLocation(), CurrentChessPieceFocus))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("approved"));
			MoveFigureToCeil();
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Moved"));
		}else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("declined"));
			CurrentChessPieceFocus = nullptr;
			CurrentCellFocus = nullptr;	
		}
		Board->HighlightCells();
	}
	else
	{
		CurrentChessPieceFocus = nullptr;
		CurrentCellFocus = nullptr;
	}
}

void AGamePawn::SwapPlayers()
{
	if(PblackCamera->IsActive())
	{
		PblackCamera->SetActive(false);
		PwhiteCamera->SetActive(true);
	}else if(PwhiteCamera->IsActive())
	{
		PblackCamera->SetActive(true);
		PwhiteCamera->SetActive(false);
	}
	CurPlayerSide == White ? CurPlayerSide = Black : CurPlayerSide = White;
}
