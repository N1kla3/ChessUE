// Fill out your copyright notice in the Description page of Project Settings.


#include "Bishop.h"

ABishop::ABishop()
    : AChessPiece()
{
    const TCHAR* pathToModel = TEXT("/Game/Shape_Cone.Shape_Cone");
    Init(pathToModel);
}

ABishop::ABishop(const TCHAR* Path)
    :AChessPiece()
{
    Init(Path);
}

TArray<FBoardLocation>& ABishop::TryForEnemyKing(FBoardLocation KingLocation)
{
    KingTrier.Empty();
    if (abs(KingLocation.Key - XBoardCoord) != abs(KingLocation.Value - YBoardCoord))
    {
        return KingTrier;
    }
    int32 XIter, YIter;
    int8 dif = abs(KingLocation.Key - XBoardCoord);
    if (KingLocation.Key > XBoardCoord)
    {
        XIter = 1;
    }else XIter = -1;
    if (KingLocation.Value > YBoardCoord)
    {
        YIter = 1;
    }else YIter = -1;
    auto temp = GetBoardLocation();
    for(auto i = 0; i < dif; i++)
    {
        temp.Key += XIter;
        temp.Value += YIter;
        KingTrier.Add(temp);
    }
    KingTrier.Add(KingLocation);
    return KingTrier;
}

bool ABishop::CanMoveToLocation(FBoardLocation cell)
{
    return true;
}

TArray<FBoardLocation>& ABishop::GetAllMoves()
{
    AllMoves.Empty();

    for (int8 i = MINlocation; i <= MAXlocation; ++i)
    {
        if (i == XBoardCoord)continue;
        const int8 Difference = abs(i - XBoardCoord);
        GoDiagonal(i, -Difference);
        GoDiagonal(i, Difference);
    }
    return AllMoves;
}

TArray<FBoardLocation>& ABishop::GetCorrectMoves(TArray<FLocWithColor>& blockCells)
{
    AllMoves.Empty();

    bool oneSide = true, secSide = true;

    for (int8 i = XBoardCoord + 1; i <= MAXlocation; i++)
    {
        const int8 Diff = abs(i-XBoardCoord);
        oneSide = GoThrowDiagonal(i, oneSide, blockCells, -Diff);
        secSide = GoThrowDiagonal(i, secSide, blockCells, Diff);
    }
    oneSide = true, secSide = true;

    for (int8 i = XBoardCoord - 1; i > 0; i--)
    {
        const int8 Diff = abs(i-XBoardCoord);
        oneSide = GoThrowDiagonal(i, oneSide, blockCells, -Diff);
        secSide = GoThrowDiagonal(i, secSide, blockCells, Diff);
    }
    return AllMoves;
}

void ABishop::GoDiagonal(const int8 Index, const int8 Diff, bool Side)
{
    if (IsOnBoard(Index, YBoardCoord + Diff) && Side)
    {
        AllMoves.Emplace(Index, YBoardCoord + Diff);
    }
}

bool ABishop::GoThrowDiagonal(const int8 Index, bool Side, TArray<FLocWithColor>& BlockCells, const int8 Diff)
{
    if (Side)
    {
        for (const auto Cell : BlockCells)
        {
            if (Cell.Key.Key == Index && Cell.Key.Value == YBoardCoord + Diff)
            {
                if(IsEnemy(Cell.Value))GoDiagonal(Index, Diff, Side);
                return false;
            }
        }
        GoDiagonal(Index, Diff, Side);
    }
    return Side;
}
