#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PortalActor.h"
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

UCLASS()
class PROD_WAKGOOD_API AMyCharacter : public ACharacter
{
    GENERATED_BODY()

private:

    // 현재 떨어지는 중 = true
    bool bFalling;

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
    
    // 캐릭터 이동 속도
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float WalkSpeed;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float SprintSpeed;

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


    UPROPERTY(EditDefaultsOnly, Category = "Montage")
    UAnimMontage* AttackMontage; // 현재 몽타주 함수 작동 안해서 미사용 변수

    // 현재 충돌 중인 포탈 오브젝트
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    APortalActor* OverlapPortal;

    // 캐릭터 상태, 현재 몽타주 함수 작동 안해서 미사용 변수
    ECharacterState State;
    ECharacterAction ActionState;

    // 캐릭터의 발 아래 가장 가까운 오브젝트
    AActor* OverlappingActor;

protected:
    // 좌우 이동
    void Move(const FInputActionValue& Value);

    // 이동 속도 조절
    void StartSprint();
    void StopSprint();

    // 점프 혹은 포탈
    void JumpOrPortal();

    // 아래로 이동
    void Down();

    // 아래로 이동 후 바닥에 닿았을 시 실행되는 함수
    virtual void Landed(const FHitResult& Hit) override;

    // 공격 : 현재 작동 안함 -> 공격 부분 블루프린터로 처리
    void Attack(const FInputActionValue& Value);

    // 변신
    void Transform();
    // 변신 해제
    void UndoTransform();
    // 특수 커맨드 1
    void SpecialCommand_1();
    // 특수 커맨드 2
    void SpecialCommand_2();

public:
    AMyCharacter();

    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // PortalAcotr에서 사용 중일 public
    void SetOverlapPortal(APortalActor* Overlap_Portal) { OverlapPortal = Overlap_Portal; }

    // 키 입력 시간 측정 시작 함수 (아래 or 가드 키 S를 누른 시점에 호출)
    void StartDown(const FInputActionValue& Value);
    // 키 입력 떼는 시간 측정 함수 (아래 or 가드 키 S를 떼는 시점 호출)
    void EndDown();
    // S키 누른 시간
    float DownPressTime;
    // 타이머
    FTimerHandle DownTimerHandle;
    // 키 중복 입력 방지
    bool bPushDDownKey = false;
    // 가드 애니메이션 실행 함수
    void Gaurd();
    // 애니메이션 블루프린트에서 사용할 변수(True일때 가드 모션)
    bool isGaurd = false;
};