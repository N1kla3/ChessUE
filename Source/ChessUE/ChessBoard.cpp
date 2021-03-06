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
    for (auto moves : FigureMoves)
    {
        if (MoveToLocation == moves)
        {
            return true;
        }
    }
    return false;
}

void AChessBoard::SetChosenPiece(AChessPiece* Piece)
{
    ChosenPiece = Piece;
    const auto ePieceColor = Piece->GetColor();
    CheckForCheck(ePieceColor);

    bIsCheckToBlack = false; //incorrect position now for debug
    bIsCheckToWhite = false;

    FigureMoves = Piece->GetCorrectMoves(GetBlockCellsForLoc(Piece->GetAllMoves()));
    FigureMoves.Add(HandleChessPawn());
    CheckLongCastling();
    CheckShortCastling();
    const bool bSideCheck = (ePieceColor == White ? bIsCheckToWhite : bIsCheckToBlack);
    /*if (bSideCheck)
    {
        WhenCheck();
        //need to do something with king
    }
    else if (IsInDefendersOfKing())
    {
        WhenDefender();
    }*/
    HighlightCells();
}

void AChessBoard::CheckForCheck(TEnumAsByte<FigureColor> Color)
{
    const FBoardLocation kingLocation = (Color == White ? WKingLocation : BKingLocation);
    for (auto enemyCell : cells)
    {
        if (auto fig = enemyCell->GetPiece())
        {
            if (fig->GetColor() != Color)
            {
                TArray<FBoardLocation> temp = fig->TryForEnemyKing(kingLocation);
                CanBeatKing(temp, fig->GetBoardLocation(), Color);
                if (temp.IsValidIndex(0))
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
TArray<FLocWithColor>& AChessBoard::GetBlockCellsForLoc(TArray<FBoardLocation> AllMoves)
{
    GetAllBlockCells();
    BlockedForFigure.Empty();

    for (const auto other : FigsLocation)
    {
        for (auto my : AllMoves)
            if (other.Key.Key == my.Key && other.Key.Value == my.Value)
            {
                BlockedForFigure.Add(other);
            }
    }

    return BlockedForFigure;
}

TArray<FLocWithColor>& AChessBoard::GetAllBlockCells()
{
    FigsLocation.Empty();
    for (auto cell : cells)
    {
        if (cell->GetPiece())
        {
            FigsLocation.Emplace(cell->GetBoardLocation(), cell->GetPiece()->GetColor());
        }
    }
    return FigsLocation;
}

void AChessBoard::CanBeatKing(TArray<FBoardLocation>& EnemyFigMoves, FBoardLocation Location,
                              TEnumAsByte<FigureColor> Color)
{
    int8 counter = 0;
    TArray<FBoardLocation> temp = EnemyFigMoves;
    EnemyFigMoves.Empty();
    const auto KingLocation = (Color == White ? WKingLocation : BKingLocation);
    for (auto moves : temp)
    {
        if (moves == KingLocation)
        {
            Color == White ? bIsCheckToWhite = true : bIsCheckToBlack = true;
            WhoBeatKing.Add(Location);
            break;
        }
        if (counter < 1)EnemyFigMoves.Add(moves);
        for (auto figs : FigsLocation)
        {
            if (figs.Key == moves)
            {
                counter++;
                break;
            }
        }
        if (counter > 1)
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
            if ((i + k) % 2 == 0)cell->InitColor(Black);
            else cell->InitColor(White);
            cells.Add(cell);
        }
    }
}

void AChessBoard::ClearCell(const FBoardLocation Location)
{
    for (auto cell : cells)
    {
        if (cell->GetBoardLocation() == Location)
        {
            cell->MoveOutPiece();
        }
    }
}

void AChessBoard::HighlightCells()
{
    for (auto moves : FigureMoves)
    {
        for (auto cell : cells)
        {
            if (moves == cell->GetBoardLocation())
            {
                cell->SwapBetweenColors();
            }
        }
    }
}

AChessPiece* AChessBoard::CreateFigureFromPawn(const FBoardLocation Location, int Switcher)
{
    ABoardCell* BeforePromotionCell = FindCell(Location);
    auto Color = BeforePromotionCell->GetPiece()->GetColor();
    BeforePromotionCell->DestroyPiece();
    switch (Switcher)
    {
        case 1:
            {
                BeforePromotionCell->SetPiece(GetWorld()->SpawnActor<ARook>(), Color);
                break;
            }
        default:
            {
                BeforePromotionCell->SetPiece(GetWorld()->SpawnActor<AKnight>(), Color);
            }
    }
    
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Knight"));
    return BeforePromotionCell->GetPiece();
}

void AChessBoard::EmptyEnPass(const FigureColor Color)
{
    if (Color == White)
    {
        WhiteEnPassant = MakeTuple(0, 0);
    }
    else
    {
        BlackEnPassant = MakeTuple(0, 0);
    }
}

void AChessBoard::SetEnPass(const FBoardLocation Location, const FigureColor Color)
{
    if (Color == White)
    {
        WhiteEnPassant = Location;
    }
    else
    {
        BlackEnPassant = Location;
    }
}

FBoardLocation AChessBoard::GetEnPass(const FigureColor Color) const
{
    return Color == White ? BlackEnPassant : WhiteEnPassant;
}

void AChessBoard::SpawnBlackFigures()
{
    cells[0 * COLUMNS]->SetPiece(GetWorld()->SpawnActor<ARook>(), Black);
    cells[7 * COLUMNS]->SetPiece(GetWorld()->SpawnActor<ARook>(), Black);

    cells[1 * COLUMNS]->SetPiece(GetWorld()->SpawnActor<AKnight>(), Black);
    cells[6 * COLUMNS]->SetPiece(GetWorld()->SpawnActor<AKnight>(), Black);

    cells[2 * COLUMNS]->SetPiece(GetWorld()->SpawnActor<ABishop>(), Black);
    cells[5 * COLUMNS]->SetPiece(GetWorld()->SpawnActor<ABishop>(), Black);

    cells[4 * COLUMNS]->SetPiece(GetWorld()->SpawnActor<AKing>(), Black);
    cells[3 * COLUMNS]->SetPiece(GetWorld()->SpawnActor<AQueen>(), Black);

    for (int i = 0; i < ROWS; i++)
    {
        cells[i * COLUMNS + 1]->SetPiece(GetWorld()->SpawnActor<AChessPawn>(), Black);
    }
    BKingLocation = FBoardLocation(5, 1);
}

void AChessBoard::SpawnWhiteFigures()
{
    cells[7]->SetPiece(GetWorld()->SpawnActor<ARook>(), White);
    cells[63]->SetPiece(GetWorld()->SpawnActor<ARook>(), White);

    cells[15]->SetPiece(GetWorld()->SpawnActor<AKnight>(), White);
    cells[55]->SetPiece(GetWorld()->SpawnActor<AKnight>(), White);

    cells[23]->SetPiece(GetWorld()->SpawnActor<ABishop>(), White);
    cells[47]->SetPiece(GetWorld()->SpawnActor<ABishop>(), White);

    cells[39]->SetPiece(GetWorld()->SpawnActor<AKing>(), White);
    cells[31]->SetPiece(GetWorld()->SpawnActor<AQueen>(), White);

    int8 shift = 6;
    for (int i = 0; i < ROWS; i++)
    {
        cells[shift]->SetPiece(GetWorld()->SpawnActor<AChessPawn>(), White);
        shift += 8;
    }
    WKingLocation = FBoardLocation(5, 8);
}

void AChessBoard::CheckShortCastling()
{
    auto King = Cast<AKing>(ChosenPiece);
    if (King)
    {
        if (King->IsMoved())return;
        int32 KingX = King->GetBoardLocation().Key;
        int32 KingY = King->GetBoardLocation().Value;
        FigureColor Color = King->GetColor();
        if (FindPiece(MakeTuple(KingX + 2, KingY)))return;
        auto Rook = Cast<ARook>(FindPiece(MakeTuple(KingX + 3, KingY)));
        if (!Rook || Rook->IsMoved())return;
        TArray<FBoardLocation> MovesToCheck;
        MovesToCheck.Emplace(KingX, KingY);
        MovesToCheck.Emplace(KingX+1, KingY);
        MovesToCheck.Emplace(KingX+2, KingY);
        if(CheckMovesForCheck(MovesToCheck, Color))
            FigureMoves.Add(King->AddShortCastling(true));
        
    }
}

void AChessBoard::CheckLongCastling()
{
    auto King = Cast<AKing>(ChosenPiece);
    if (King)
    {
        if (King->IsMoved())return;
        int32 KingX = King->GetBoardLocation().Key;
        int32 KingY = King->GetBoardLocation().Value;
        FigureColor Color = King->GetColor();
        if (FindPiece(MakeTuple(KingX - 2, KingY)))return;
        auto Rook = Cast<ARook>(FindPiece(MakeTuple(KingX - 4, KingY)));
        if (!Rook || Rook->IsMoved())return;
        TArray<FBoardLocation> MovesToCheck;
        MovesToCheck.Emplace(KingX, KingY);
        MovesToCheck.Emplace(KingX-1, KingY);
        MovesToCheck.Emplace(KingX-2, KingY);
        if(CheckMovesForCheck(MovesToCheck, Color))
            FigureMoves.Add(King->AddLongCastling(true));
    }
}

void AChessBoard::DoShortCastling(FBoardLocation KingLocation)
{
    auto One = FindCell(MakeTuple(KingLocation.Key+1, KingLocation.Value));
    auto Two = FindCell(MakeTuple(KingLocation.Key+3, KingLocation.Value));
    SwapCellPieces(*One, *Two);
}

void AChessBoard::DoLongCastling(FBoardLocation KingLocation)
{
    auto One = FindCell(MakeTuple(KingLocation.Key-1, KingLocation.Value));
    auto Two = FindCell(MakeTuple(KingLocation.Key-4, KingLocation.Value));
    SwapCellPieces(*One, *Two);
}

ABoardCell* AChessBoard::FindCell(const FBoardLocation Location)
{
    for(auto Cell : cells)
    {
        if(Cell->GetBoardLocation() == Location)
        {
            return Cell;
        }
    }
    return nullptr;
}

void AChessBoard::SwapCellPieces(ABoardCell& First, ABoardCell& Second)
{
    auto Piece = Second.GetPiece();
    if(Piece)
    {
        Second.MoveOutPiece();
        First.SetPiece(Piece, Piece->GetColor());
    }
}

bool AChessBoard::CheckMovesForCheck(TArray<FBoardLocation>& Moves, FigureColor MoverColor)
{
    for (auto enemyCell : cells)
    {
        auto Fig = enemyCell->GetPiece();
        if (Fig && Fig->GetColor() != MoverColor)
        {
            int8 SpecCoff = 1;
            for (auto Move : Moves)
            {
                TArray<FBoardLocation> Temp = Fig->TryForEnemyKing(Move);
                if(CheckOrNot(Temp, SpecCoff))
                {
                    return false;
                }
                if(SpecCoff == 1)SpecCoff--; 
            }
        }
    }
    return true;
}

bool AChessBoard::CheckOrNot(TArray<FBoardLocation>& DangerMoves, int8 Count)
{
    if(!DangerMoves.IsValidIndex(0))return false;
    auto Blocks = GetBlockCellsForLoc(DangerMoves);
    int8 LocalCount = 0;
    for(auto Move : DangerMoves)
    {
        for(auto Block : Blocks)
        {
            if(Move == Block.Key)
            {
                LocalCount++;   
            }
        }
    }
    return LocalCount > Count ? false : true;
}

FBoardLocation AChessBoard::HandleChessPawn()
{
    auto IfPawn = Cast<AChessPawn>(ChosenPiece);
    if (IfPawn)
    {
        FigureColor Color = IfPawn->GetColor();
        auto EnPassLocation = Color == White ? BlackEnPassant : WhiteEnPassant;
        return IfPawn->CheckEnPassant(EnPassLocation);
    }
    return MakeTuple(0, 0);
}

AChessPiece* AChessBoard::FindPiece(const FBoardLocation PieceLocation)
{
    for (auto Cell : cells)
    {
        if (Cell->GetBoardLocation().Key == PieceLocation.Key
            && Cell->GetBoardLocation().Value == PieceLocation.Value)
        {
            if (Cell->GetPiece())return Cell->GetPiece();
        }
    }
    return nullptr;
}

bool AChessBoard::IsInDefendersOfKing()
{
    for (auto pair : PossibleChecks)
    {
        for (auto i : pair.Value)
        {
            if (i == ChosenPiece->GetBoardLocation())
            {
                return true;
            }
        }
    }
    return false;
}

void AChessBoard::WhenDefender()
{
    auto temp = FigureMoves;
    FigureMoves.Empty();
    FBoardLocation key;
    for (auto pair : PossibleChecks)
    {
        for (auto i : pair.Value)
        {
            if (i == ChosenPiece->GetBoardLocation())
            {
                key = pair.Key;
                break;
            }
        }
    }
    TArray<FBoardLocation> local = *PossibleChecks.Find(key);
    for (auto i : local)
    {
        for (auto k : temp)
        {
            if (k == i)
            {
                FigureMoves.Add(k);
            }
        }
    }
}

void AChessBoard::WhenCheck()
{
    auto temp = FigureMoves;
    FigureMoves.Empty();
    for (auto beaters : WhoBeatKing)
    {
        for (auto myMoves : temp)
        {
            if (myMoves == beaters)
            {
                FigureMoves.Add(myMoves);
            }
        }
        for (auto beatersMoves : *PossibleChecks.Find(beaters))
        {
            for (auto myMoves : temp)
            {
                if (myMoves == beatersMoves)
                {
                    FigureMoves.Add(myMoves);
                }
            }
        }
    }
}

void AChessBoard::MakeMovesNoCheck()
{
}
