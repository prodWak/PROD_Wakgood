#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PortalActor.h"
#include "LadderActor.h"
#include "MyCharacter.generated.h"

// 캐릭터 무기 ENUM (공격을 코드로 실패해서 임시로 BP_MyCharacter 블루 프린트로 구현해놓아서 현재는 안쓰임)
UENUM(BlueprintType)
enum class ECharacterState : uint8
{
    NONE,
    ONE_HAND_GUN,
};

// 캐릭터 액션 ENUM (공격을 코드로 실패해서 임시로 BP_MyCharacter 블루 프린트로 구현해놓아서 현재는 안쓰임)
UENUM(BlueprintType)
enum class ECharacterAction : uint8
{
    IDLE,
    ATTACK,
};

// 전방 선언
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class USkeletalMeshComponent;
class UAnimMontage;
class APortalActor;
class ALadderActor;

UCLASS()
class PROD_WAKGOOD_API AMyCharacter : public ACharacter
{
    GENERATED_BODY()

private:

    // 현재 떨어지는 중 = true
    bool bFalling;
    
    // K키를 누른 상태인지 확인하는 변수
    bool bKKeyPressed;

    // J키를 누른 상태인지 확인하는 변수
    bool bJKeyPressed;

    // A,D를 누른 상태인지 확인하는 변수
    bool bMoveKeyPressed;

    // 메시 방향을 돌려주는 함수
    void RotateMesh(bool bIsMovingRight);
    // 현재 설정된 몽타주를 실행해주는 함수 (현재 작동 안함)
    void PlayAnimMontage();

protected:
    virtual void BeginPlay() override;

    // 컴포넌트*************************************
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCameraComponent* Camera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USkeletalMeshComponent* MyMesh;
    // *********************************컴포넌트
    
    // 캐릭터 이동 속도*********************************
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float WalkSpeed;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float SprintSpeed;
    // *********************************캐릭터 이동 속도
    
    // InputSystem 맵핑***********************************
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "input")
    UInputMappingContext* MappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "input")
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "input")
    UInputAction* JumpOrPortalAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "input")
    UInputAction* RunAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "input")
    UInputAction* DownAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "input")
    UInputAction* AttackAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "input")
    UInputAction* SpecialCommandAction_1;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "input")
    UInputAction* SpecialCommandAction_2;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "input")
    UInputAction* TransformAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "input")

    UInputAction* UndoTransformAction;
    // ************************************** InputSystem 맵핑

     // 현재 몽타주 함수 작동 안해서 미사용 변수
    UPROPERTY(EditDefaultsOnly, Category = "Montage")
    UAnimMontage* AttackMontage;

    // 현재 충돌 중인 포탈 오브젝트
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    APortalActor* OverlapPortal;

    // 현재 충돌 중인 사다리 오브젝트
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    ALadderActor* OverlapLadder;

    // 캐릭터 상태, 현재 몽타주 함수 작동 안해서 미사용 변수
    ECharacterState State;
    ECharacterAction ActionState;

    // 캐릭터의 발 아래 가장 가까운 오브젝트
    AActor* OverlappingActor;

    // 애니메이션 블루프린트에서 사용할 변수(True일때 가드 모션)
    bool isGaurd = false;

    // 애니메이션 블루프린트에서 사용할 변수(True일때 포획 모션)
    bool isCapture;

    // 키 누른 시간
    float DownPressTime;
    // 타이머
    FTimerHandle DownTimerHandle;
    // 키 중복 입력 방지
    bool bPushDDownKey = false;

protected:
    // 좌우 이동
    void Move(const FInputActionValue& Value);
    void MoveEnd();
    // 이동 속도 조절
    void SprintCheck();
    void StartSprint();
    void StopSprint();

    // 점프 혹은 포탈
    void JumpOrPortalOrLadder(const FInputActionValue& Value);
    // 아래로 이동 후 바닥에 닿았을 시 실행되는 함수
    virtual void Landed(const FHitResult& Hit) override;

    // 키 입력 시간 측정 시작 함수 (아래 or 가드 키 S를 누른 시점에 호출)
    void DownPressed();
    // 키 입력 떼는 시간 측정 함수 (아래 or 가드 키 S를 떼는 시점 호출)
    void DownReleased();
    // 아래로 이동
    void Down();
    // 가드 애니메이션 실행 함수
    void Gaurd();
    
    // 키 입력 시간 측정 시작 함수 (J 키를 누른 시점에 호출)
    void AttackPressed();
    // 키 입력 떼는 시간 측정 함수 (J 키를 떼는 시점 호출)
    void AttackReleased();
    // 공격 : 현재 작동 안함
    void Attack();
    // 커맨드를 이용한 공격
    void CommandAttack();
    // 포획 애니메이션 실행 함수
    void Capture();

    // 특수 커맨드 1 : K
    void SpecialCommand_1(const FInputActionValue& Value);
    void SpecialCommand_1_Pressed();
    void SpecialCommand_1_Released();
    void HoveringDown();
    
    // 특수 커맨드 2 : J
    void SpecialCommand_2();

    // 변신
    void Transform();
    // 변신 해제
    void UndoTransform();

public:
    AMyCharacter();

    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


    // 포탈과 오버랩 시 현재 포탈 데이터를 저장
    void SetOverlapPortal(APortalActor* Overlap_Portal) { OverlapPortal = Overlap_Portal; }
    // 사다리와 오버랩 시 현재 사다리 데이터를 저장
    void SetOverlapLadder(ALadderActor* Overlap_Ladder) { OverlapLadder = Overlap_Ladder; }
    // 캐릭터 상태를 Flying으로 전환
    void SetLadderStartState();
    // 캐릭터 상태를 Walking으로 전환
    void SetLadderEndState();

    void Forword(const FInputActionValue& Value);
};