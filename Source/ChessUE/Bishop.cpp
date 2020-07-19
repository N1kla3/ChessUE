// Fill out your copyright notice in the Description page of Project Settings.


#include "Bishop.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

ABishop::ABishop()
    : AChessPiece()
{
    const TCHAR* pathToModel = TEXT("/Game/Shape_Cone.Shape_Cone");
    Init(pathToModel);
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
    return KingTrier;
}

bool ABishop::CanMoveToLocation(FBoardLocation cell)
{
    return true;
}

TArray<FBoardLocation>& ABishop::GetAllMoves()
{
    AllMoves.Empty();

    for (size_t i = MINlocation; i <= MAXlocation; ++i)
    {
        if (i == XBoardCoord)continue;
        const int32 Difference = UKismetMathLibrary::Abs_Int(i - XBoardCoord);
        if (IsOnBoard(i, YBoardCoord - Difference))
        {
            AllMoves.Emplace(i, YBoardCoord - Difference);
        }
        if (IsOnBoard(i, YBoardCoord + Difference))
        {
            AllMoves.Emplace(i, YBoardCoord + Difference);
        }
    }
    return AllMoves;
}

TArray<FBoardLocation>& ABishop::GetCorrectMoves(TArray<FBoardLocation>& blockCells)
{
    TArray<FBoardLocation> temp;

    bool oneSide = true, secSide = true;

    for (size_t i = XBoardCoord + 1; i <= MAXlocation; i++)
    {
        if (oneSide)
        {
            for (auto k : blockCells)
            {
                if (k.Key == i && k.Value == YBoardCoord - i)
                {
                    oneSide = false;
                }
            }
            if (IsOnBoard(i, YBoardCoord - i) && oneSide)
            {
                temp.Emplace(i, YBoardCoord - i);
            }
        }
        if (secSide)
        {
            for (auto k : blockCells)
            {
                if (k.Key == i && k.Value == YBoardCoord + i)
                {
                    secSide = false;
                }
            }
            if (IsOnBoard(i, YBoardCoord + i) && secSide)
            {
                temp.Emplace(i, YBoardCoord + i);
            }
        }
    }
    oneSide = true, secSide = true;

    for (size_t i = XBoardCoord - 1; i > 0; i--)
    {
        if (oneSide)
        {
            for (auto k : blockCells)
            {
                if (k.Key == i && k.Value == YBoardCoord - i)
                {
                    oneSide = false;
                }
            }
            if (IsOnBoard(i, YBoardCoord - i) && oneSide)
            {
                temp.Emplace(i, YBoardCoord - i);
            }
        }
        if (secSide)
        {
            for (auto k : blockCells)
            {
                if (k.Key == i && k.Value == YBoardCoord + i)
                {
                    secSide = false;
                }
            }
            if (IsOnBoard(i, YBoardCoord + i) && secSide)
            {
                temp.Emplace(i, YBoardCoord + i);
            }
        }
    }
    AllMoves = temp;

    return AllMoves;
}
