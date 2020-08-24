// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePawn.h"

#include "BoardCell.h"
#include "ChessPawn.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "King.h"
#include "Rook.h"
#include "UObject/ConstructorHelpers.h"
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

	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetConstruct(TEXT("/Game/PieceChoser"));
	Widget = WidgetConstruct.Class;
}


void AGamePawn::CreatePieceInGUI()
{
	CurrentChessPieceFocus = Board->CreateFigureFromPawn(CurrentChessPieceFocus->GetBoardLocation(), FigureCreatorIndex);
	MoveFigureToCeil();
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameAndUI());
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
	Board->ClearCell(CurrentChessPieceFocus->GetBoardLocation());
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
		if(Board->CheckEverything(CurrentCellFocus->GetBoardLocation()))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("approved"));
			HandleChessPawn(CurrentCellFocus->GetBoardLocation());			
			IncreaseMoveIfKing();
			IncreaseMoveIfRook();
			MakeCastlingIfNeeded(CurrentCellFocus->GetBoardLocation());
			if(!IsTimeToPromotePawn(CurrentCellFocus->GetBoardLocation()))
				MoveFigureToCeil();
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Moved"));
		}else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("declined"));
			CurrentChessPieceFocus = nullptr;
			CurrentCellFocus = nullptr;	
		}
	}
	else
	{
		CurrentChessPieceFocus = nullptr;
		CurrentCellFocus = nullptr;
	}
	Board->HighlightCells();
}

void AGamePawn::HandleChessPawn(const FBoardLocation ToMove)
{
	auto IfPawn = Cast<AChessPawn>(CurrentChessPieceFocus);
	if(IfPawn)
	{
		const FigureColor Color = IfPawn->GetColor();
		if(IfPawn->GetCurrentMoveNumber() == 0)
		{
			if(abs(IfPawn->GetBoardLocation().Value - ToMove.Value) == 2)
			{
				Board->SetEnPass(ToMove, Color);		
			}
		}else
		{
			Board->EmptyEnPass(Color);
		}
		IfPawn->IncrementCurrentMoveNumber();
		auto YenPass = Board->GetEnPass(IfPawn->GetColor());
		auto YToMove = ToMove.Value;
		auto Coff = Color == White ? 1 : -1;
		if(YenPass.Value - YToMove == Coff)
		{
			auto Cell = Board->FindCell(YenPass);
			Cell->DestroyPiece();
			Cell->MoveOutPiece();
		}
	}else
	{
		Board->EmptyEnPass(CurrentChessPieceFocus->GetColor());
	}
	
}

void AGamePawn::IncreaseMoveIfRook()
{
	auto Rook = Cast<ARook>(CurrentChessPieceFocus);
	if(Rook)
		Rook->Moved();
}

void AGamePawn::IncreaseMoveIfKing()
{
	auto King = Cast<AKing>(CurrentChessPieceFocus);
	if(King)
		King->Moved();
}

void AGamePawn::MakeCastlingIfNeeded(const FBoardLocation ToMoveLocation)
{
	auto King = Cast<AKing>(CurrentChessPieceFocus);
	if(King)
	{
		const FBoardLocation Loc = King->GetBoardLocation();
		if(Loc.Key - ToMoveLocation.Key == 2)
		{
			Board->DoLongCastling(Loc);
		}else if(Loc.Key - ToMoveLocation.Key == -2)
		{
			Board->DoShortCastling(Loc);
		}
	}
}

bool AGamePawn::IsTimeToPromotePawn(const FBoardLocation ToMove)
{
	auto IfPawn = Cast<AChessPawn>(CurrentChessPieceFocus);
	if(IfPawn)
	{
		if(IfPawn->IsPromotionTime(ToMove))
		{
			ChooserWidget = CreateWidget<UPieceChooserWidget>(GetWorld(), Widget);
			ChooserWidget->AddToViewport();
			GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
			return true;
		}
	}
	return false;
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
