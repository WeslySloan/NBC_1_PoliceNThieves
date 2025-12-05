// PoliceNThieves/Public/APolicePlayerState.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h" // DOREPLIFETIME 매크로를 위해 필요
#include "PoliceNThieves.h" // EPlayerRole Enum이 정의된 헤더 파일 (프로젝트명에 따라 다를 수 있음)

#include "APolicePlayerState.generated.h"

/**
 * */
UCLASS()
class POLICENTHIEVES_API APolicePlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    APolicePlayerState();

    // 이 함수를 오버라이드해야 복제 변수들을 등록할 수 있습니다.
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // 역할 설정 (서버 전용)
    void SetPlayerRole(EPlayerRole NewRole);

    // 역할 가져오기
    FORCEINLINE EPlayerRole GetPlayerRole() const { return PlayerRole; }

protected:
    // **경찰/도둑 역할 복제 변수**
    // BlueprintReadOnly를 추가하여 경고 해결 및 블루프린트에서 읽기 가능하게 설정
    UPROPERTY(ReplicatedUsing = OnRep_PlayerRole, BlueprintReadOnly, Category = "Role")
    EPlayerRole PlayerRole = EPlayerRole::EPR_None;

private:
    // 역할이 복제될 때마다 클라이언트에서 실행될 함수 (UI 업데이트 등에 사용)
    UFUNCTION()
    void OnRep_PlayerRole();
};