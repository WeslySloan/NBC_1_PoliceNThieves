// PoliceNThieves/Private/APolicePlayerState.cpp

#include "APolicePlayerState.h"
#include "Net/UnrealNetwork.h" // DOREPLIFETIME 매크로를 위해 다시 포함

APolicePlayerState::APolicePlayerState()
{
    // 기본 초기화 (Enum 정의에 따라 EPR_None으로 자동 초기화됩니다)
}

// ----------------------------------------------------
// 네트워크 복제 설정
// ----------------------------------------------------

void APolicePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // PlayerRole 변수를 복제 대상에 등록합니다.
    DOREPLIFETIME(APolicePlayerState, PlayerRole);
}

// ----------------------------------------------------
// 역할 설정 및 업데이트
// ----------------------------------------------------

void APolicePlayerState::SetPlayerRole(EPlayerRole NewRole)
{
    // 이 함수는 서버(Authority)에서만 호출되어야 합니다.
    if (GetLocalRole() == ROLE_Authority)
    {
        // 1. 서버 변수 값 변경
        PlayerRole = NewRole;

        // 2. 서버에서 변수를 변경했으므로, 복제 이외에도 OnRep 함수를 직접 호출하여
        //    서버에서도 UI 업데이트 등의 로직이 실행되도록 합니다.
        OnRep_PlayerRole();
    }
}

void APolicePlayerState::OnRep_PlayerRole()
{
    // 이 함수는 서버에서 PlayerRole 값이 변경되어 클라이언트로 전송되었을 때
    // 클라이언트에서 자동으로 실행됩니다. (서버에서는 SetPlayerRole에 의해 수동 호출됨)

    // 현재 역할이 무엇인지 로그로 출력하여 확인합니다.
    FString RoleString = UEnum::GetValueAsString(TEXT("EPlayerRole"), PlayerRole);

    // 클라이언트의 화면에만 메시지를 띄우는 GEngine 디버그 메시지
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            -1,
            5.f,
            FColor::Yellow,
            FString::Printf(TEXT("My Role is: %s"), *RoleString)
        );
    }

    UE_LOG(LogTemp, Warning, TEXT("PlayerState Updated! My Role: %s"), *RoleString);

    // TODO: 여기에 역할에 따른 UI 변경 (예: 경찰 마크 표시, 도둑 HUD 숨기기 등) 로직을 추가합니다.
}