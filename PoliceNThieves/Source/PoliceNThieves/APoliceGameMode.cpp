// APoliceGameMode.cpp

#include "APoliceGameMode.h"
#include "APolicePlayerState.h" 
#include "APolicePlayerController.h" // 새로 생성된 컨트롤러 포함
#include "PoliceNThieves.h" // EPlayerRole Enum을 위해 포함
#include "Kismet/GameplayStatics.h" 

APoliceGameMode::APoliceGameMode()
{
    // 🚨 플레이어 컨트롤러 클래스 설정 (블루프린트 설정과 일치해야 함)
    PlayerControllerClass = APolicePlayerController::StaticClass();

    // APolicePlayerState를 기본 PlayerState로 사용하도록 설정
    PlayerStateClass = APolicePlayerState::StaticClass();

    // 최소 플레이어 수 초기화
    MinPlayersToStart = 2;
}

void APoliceGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    // 1. 새로운 플레이어를 대기열에 추가 (서버에서 관리)
    WaitingPlayers.Add(NewPlayer);

    // 2. 현재 접속한 플레이어 수 확인 및 게임 시작 조건 검토
    if (WaitingPlayers.Num() >= MinPlayersToStart)
    {
        // 최소 인원 충족 시 로그 출력
        UE_LOG(LogTemp, Warning, TEXT("Minimum players reached! Starting role assignment."));
        AssignRoles();
    }
}

void APoliceGameMode::AssignRoles()
{
    if (WaitingPlayers.Num() < 2)
    {
        UE_LOG(LogTemp, Error, TEXT("AssignRoles called but less than 2 players are waiting."));
        return;
    }

    // 1. 역할 배정을 위해 플레이어 목록을 섞습니다.
    const int32 MaxIndex = WaitingPlayers.Num() - 1;
    const int32 RandomIndex = FMath::RandRange(0, MaxIndex);

    APlayerController* PoliceController = WaitingPlayers[RandomIndex];
    int32 ThiefIndex = (RandomIndex == 0 && MaxIndex >= 1) ? 1 : 0;
    APlayerController* ThiefController = WaitingPlayers[ThiefIndex];

    // 3. PlayerState에 역할 저장 및 디버그 로그 출력
    if (APolicePlayerState* PolicePS = PoliceController->GetPlayerState<APolicePlayerState>())
    {
        PolicePS->SetPlayerRole(EPlayerRole::EPR_Police);
        UE_LOG(LogTemp, Error, TEXT("ROLE ASSIGNED: Police -> %s"), *PolicePS->GetPlayerName());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ASSIGN ROLES FAILED: Police PlayerState is NULL for Controller %s"), *PoliceController->GetName());
    }

    if (APolicePlayerState* ThiefPS = ThiefController->GetPlayerState<APolicePlayerState>())
    {
        ThiefPS->SetPlayerRole(EPlayerRole::EPR_Thief);
        UE_LOG(LogTemp, Error, TEXT("ROLE ASSIGNED: Thief -> %s"), *ThiefPS->GetPlayerName());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ASSIGN ROLES FAILED: Thief PlayerState is NULL for Controller %s"), *ThiefController->GetName());
    }

    WaitingPlayers.Empty();
}