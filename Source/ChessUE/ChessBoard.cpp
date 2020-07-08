// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessBoard.h"

#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "ChessPawn.h"

#include "Engine/World.h"

// Sets default values
AChessBoard::AChessBoard()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    ROWS = 8;
    COLUMNS = 8;
    Space = 100.0;

    URoot = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
    RootComponent = URoot;
}

// Called when the game starts or when spawned
void AChessBoard::BeginPlay()
{
    Super::BeginPlay();
    SpawnCells();
    SpawnBlackFigures();
    SpawnWhiteFigures();
}

// Called every frame
void AChessBoard::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool AChessBoard::CheckEverything(FBoardLocation MoveToLocation)
{
    return true;
}

void AChessBoard::SetChosenPiece(AChessPiece* Piece)
{
    ChosenPiece = Piece;
    const auto ePieceColor = Piece->GetColor();
    CheckForCheck(ePieceColor);

    bIsCheckToBlack = false;
    bIsCheckToWhite = false;
    
    FigureMoves = Piece->GetCorrectMoves(GetBlockCellsForLoc(Piece->GetAllMoves()));

    const bool bSideCheck = (ePieceColor == White ? bIsCheckToWhite : bIsCheckToBlack);
    if(bSideCheck)
    {
        //can move only to cells that can defend king (compare with own possible)
    }else
    {
        if(IsInDefendersOfKing())
        {
            
        }
        else
        {
            
        }
    }
}

void AChessBoard::CheckForCheck(TEnumAsByte<FigureColor> Color)
{
    const FBoardLocation kingLocation = (Color == White ? WKingLocation : BKingLocation);
    for(auto enemyCell : cells)
    {
        if(auto fig = enemyCell->GetPiece())
        {
            if(fig->GetColor() != Color)
            {
                TArray<FBoardLocation> temp = fig->TryForEnemyKing(kingLocation);
                CanBeatKing(temp, Color);
                if(temp.IsValidIndex(0))
                {
                    PossibleChecks.Add(fig->GetBoardLocation(), temp);
                }
            }
        }
    }
}

bool AChessBoard::CheckForMate()
{
    return true;
}

/**
 * \brief Gets All moves of figure and return locations of figures placed on that moves 
 * \param AllMoves 
 * \return 
 */
TArray<FBoardLocation>& AChessBoard::GetBlockCellsForLoc(TArray<FBoardLocation> AllMoves)
{
    FigureMoves.Empty();
    GetAllBlockCells();
    
    for (const auto other : FigsLocation)
    {
        for(auto my : FigureMoves)
        if (other.Key == my.Key && other.Value == my.Value)
        {
            FigureMoves.Add(my);
        }
    }

    return FigureMoves;
}

TArray<FBoardLocation>& AChessBoard::GetAllBlockCells()
{
    FigsLocation.Empty();
    for (auto cell : cells)
    {
        if (cell->GetPiece())
        {
            FigsLocation.Add(cell->GetBoardLocation());
        }
    }
    return FigsLocation;
}

void AChessBoard::CanBeatKing(TArray<FBoardLocation>& EnemyFigMoves, TEnumAsByte<FigureColor> Color)
{
    int8 counter = 0;
    TArray<FBoardLocation> temp = EnemyFigMoves;
    EnemyFigMoves.Empty();
    const auto KingLocation = (Color == White ? WKingLocation : BKingLocation);
    for(auto moves : temp)
    {
        if(moves == KingLocation)
        {
            Color == White ? bIsCheckToWhite = true : bIsCheckToBlack = true;
            break;
        }
        if(counter < 1)EnemyFigMoves.Add(moves);
        for(auto figs : FigsLocation)
        {
            if(figs == moves)
            {
                
                counter++;
                break;
            }
        }
        if(counter > 1)
        {
            EnemyFigMoves.Empty();
            return;       
        }
    }
}

void AChessBoard::SpawnCells()
{
    FVector curActorLocation = GetActorLocation();

    for (int32 i = 1; i <= ROWS; i++)
    {
        for (int32 k = 1; k <= COLUMNS; k++)
        {
            FRotator rotation = FRotator(0.f, 0.f, 0.f);
            FVector spawnLocation = curActorLocation + FVector(Space * i, Space * k, 0.f);
            ABoardCell* cell = GetWorld()->SpawnActor<ABoardCell>(spawnLocation, rotation);
            cell->SetBoardLocation(FBoardLocation(i, k));
            cells.Add(cell);
        }
    }
}

void AChessBoard::SpawnBlackFigures()
{
    cells[0 * COLUMNS]->SetPiece(GetWorld()->SpawnActor<ARook>(), Black);
    cells[7 * COLUMNS]->SetPiece(GetWorld()->SpawnActor<ARook>(), Black);

    cells[1 * COLUMNS]->SetPiece(GetWorld()->SpawnActor<AKnight>(), Black);
    cells[6 * COLUMNS]->SetPiece(GetWorld()->SpawnActor<AKnight>(), Black);

    cells[2 * COLUMNS]->SetPiece(GetWorld()->SpawnActor<ABishop>(), Black);
    cells[5 * COLUMNS]->SetPiece(GetWorld()->SpawnActor<ABishop>(), Black);

    cells[3 * COLUMNS]->SetPiece(GetWorld()->SpawnActor<AKing>(), Black);
    cells[4 * COLUMNS]->SetPiece(GetWorld()->SpawnActor<AQueen>(), Black);

    for (int i = 0; i < ROWS; i++)
    {
        cells[i * COLUMNS + 1]->SetPiece(GetWorld()->SpawnActor<AChessPawn>(), Black);
    }
}

void AChessBoard::SpawnWhiteFigures()
{
    cells[7]->SetPiece(GetWorld()->SpawnActor<ARook>(), White);
    cells[47]->SetPiece(GetWorld()->SpawnActor<ARook>(), White);

    cells[15]->SetPiece(GetWorld()->SpawnActor<AKnight>(), White);
    cells[55]->SetPiece(GetWorld()->SpawnActor<AKnight>(), White);

    cells[23]->SetPiece(GetWorld()->SpawnActor<ABishop>(), White);
    cells[63]->SetPiece(GetWorld()->SpawnActor<ABishop>(), White);

    cells[39]->SetPiece(GetWorld()->SpawnActor<AKing>(),White);
    cells[31]->SetPiece(GetWorld()->SpawnActor<AQueen>(), White);

    int8 shift = 6;
    for (int i = 0; i < ROWS; i++)
    {
        cells[shift]->SetPiece(GetWorld()->SpawnActor<AChessPawn>(), White);
        shift += 8;
    }
}

bool AChessBoard::IsInDefendersOfKing()
{
    if(PossibleChecks.Contains(ChosenPiece->GetBoardLocation()))
    {
        return true;
    }
    return false;
}

void AChessBoard::MakeMovesNoCheck()
{
    
}
