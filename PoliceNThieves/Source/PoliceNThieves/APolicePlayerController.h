// APolicePlayerController.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "APolicePlayerController.generated.h"

/**
 * 게임의 로컬/서버 제어 및 PlayerState가 준비되었는지 확인하는 역할
 */
UCLASS()
class POLICENTHIEVES_API APolicePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APolicePlayerController();
};