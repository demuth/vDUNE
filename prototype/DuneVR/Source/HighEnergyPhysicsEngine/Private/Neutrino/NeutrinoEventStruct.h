#pragma once

#include "CoreMinimal.h"
#include "NeutrinoEventStruct.generated.h"

USTRUCT()
struct FEventMetaData
{
    GENERATED_BODY()

public:
    UPROPERTY()
    double TotalCharge;

    UPROPERTY()
    double Density;

    UPROPERTY()
    double XAxisMaximum;

    UPROPERTY()
    double XAxisMinimum;

    UPROPERTY()
    double YAxisMaximum;

    UPROPERTY()
    double YAxisMinimum;

    UPROPERTY()
    double ZAxisMaximum;

    UPROPERTY()
    double ZAxisMinimum;
};

USTRUCT()
struct FNeutrinoPointData
{
    GENERATED_BODY()

public:
    UPROPERTY()
    int32 Id;

    UPROPERTY()
    float X;

    UPROPERTY()
    float Y;

    UPROPERTY()
    float Z;

    UPROPERTY()
    float Charge;
};

USTRUCT()
struct FNeutrinoTrackData
{
    GENERATED_BODY()

public:
    UPROPERTY()
    int32 Id;

    UPROPERTY()
    TArray<FNeutrinoPointData> Points;

    UPROPERTY()
    FEventMetaData Metadata;
};

USTRUCT()
struct FNeutrinoEventData
{
    GENERATED_BODY()

public:
    UPROPERTY()
    int32 Id;

    UPROPERTY()
    TArray<FNeutrinoTrackData> Tracks;

    UPROPERTY()
    FEventMetaData Metadata;
};

USTRUCT()
struct FNeutrinoEventList
{
    GENERATED_BODY();

public:
    UPROPERTY()
    TArray<FNeutrinoEventData> EventList;
};