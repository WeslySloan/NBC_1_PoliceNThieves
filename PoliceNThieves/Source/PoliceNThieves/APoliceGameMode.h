// APoliceGameMode.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "APoliceGameMode.generated.h"

UCLASS()
class POLICENTHIEVES_API APoliceGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    APoliceGameMode();

    // AGameModeBase의 함수를 오버라이드하여 플레이어 접속 시 호출
    virtual void PostLogin(APlayerController* NewPlayer) override;

    // 게임 시작 시 경찰/도둑 역할을 배정하는 함수 (서버 전용)
    void AssignRoles();

private:
    // 게임 시작에 필요한 최소 플레이어 수
    UPROPERTY(EditDefaultsOnly, Category = "GameRules")
    int32 MinPlayersToStart = 2;

    // 현재 역할이 할당되지 않은 플레이어의 목록
    TArray<APlayerController*> WaitingPlayers;
};