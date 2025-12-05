// APoliceGameMode.cpp 파일

#include "APoliceGameMode.h"
#include "APolicePlayerState.h" // 우리가 만든 PlayerState 헤더 포함
#include "Kismet/GameplayStatics.h" // UGameplayStatics를 위해 포함

APoliceGameMode::APoliceGameMode()
{
    // 프로젝트 목표: 우리가 만든 APolicePlayerState를 기본 PlayerState로 사용하도록 설정
    PlayerStateClass = APolicePlayerState::StaticClass();

    // 프로젝트 목표: ThirdPersonCharacter 대신 우리가 만든 BP_PoliceCharacter를 사용하도록 설정 (선택 사항)
    // DefaultPawnClass = APoliceNThievesCharacter::StaticClass(); 

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
        // TODO: 실제 프로젝트에서는 여기에 매치 스테이트를 'InProgress'로 바꾸는 로직이 들어감.
    }
}

void APoliceGameMode::AssignRoles()
{
    // 이 함수는 서버에서 MinPlayersToStart 조건을 만족했을 때 호출됩니다.

    if (WaitingPlayers.Num() < 2) return; // 2명이 안 되면 함수 종료

    // 1. 역할 배정을 위해 플레이어 목록을 섞습니다.
    const int32 MaxIndex = WaitingPlayers.Num() - 1;
    const int32 RandomIndex = FMath::RandRange(0, MaxIndex);

    // 2. 경찰/도둑 역할 배정
    APlayerController* PoliceController = WaitingPlayers[RandomIndex];

    // 남은 플레이어 중 한 명을 도둑으로 배정합니다.
    int32 ThiefIndex = (RandomIndex == 0 && MaxIndex >= 1) ? 1 : 0;
    APlayerController* ThiefController = WaitingPlayers[ThiefIndex];

    // 3. PlayerState에 역할 저장 (PlayerState는 모든 클라이언트에게 복제됨)
    if (APolicePlayerState* PolicePS = PoliceController->GetPlayerState<APolicePlayerState>())
    {
        PolicePS->SetPlayerRole(EPlayerRole::EPR_Police);
        UE_LOG(LogTemp, Error, TEXT("ROLE ASSIGNED: Police -> %s"), *PolicePS->GetPlayerName());
    }

    if (APolicePlayerState* ThiefPS = ThiefController->GetPlayerState<APolicePlayerState>())
    {
        ThiefPS->SetPlayerRole(EPlayerRole::EPR_Thief);
        UE_LOG(LogTemp, Error, TEXT("ROLE ASSIGNED: Thief -> %s"), *ThiefPS->GetPlayerName());
    }

    // 역할 배정 완료 후 대기열을 비웁니다. (선택 사항)
    WaitingPlayers.Empty();
}