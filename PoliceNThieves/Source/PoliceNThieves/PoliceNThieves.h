// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPlayerRole : uint8
{
    EPR_None UMETA(DisplayName = "None"),
    EPR_Police UMETA(DisplayName = "Police"),
    EPR_Thief UMETA(DisplayName = "Thief"),
    EPR_Citizen UMETA(DisplayName = "Citizen") // AI 시민을 위한 역할도 정의
};