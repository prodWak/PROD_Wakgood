#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PortalActor.h"
#include "LadderActor.h"
#include "MyCharacter.generated.h"

// ĳ���� ���� ENUM (������ �ڵ�� �����ؼ� �ӽ÷� BP_MyCharacter ��� ����Ʈ�� �����س��Ƽ� ����� �Ⱦ���)
UENUM(BlueprintType)
enum class ECharacterState : uint8
{
    NONE,
    ONE_HAND_GUN,
};

// ĳ���� �׼� ENUM (������ �ڵ�� �����ؼ� �ӽ÷� BP_MyCharacter ��� ����Ʈ�� �����س��Ƽ� ����� �Ⱦ���)
UENUM(BlueprintType)
enum class ECharacterAction : uint8
{
    IDLE,
    ATTACK,
};

// ���� ����
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

    // ���� �������� �� = true
    bool bFalling;
    
    // KŰ�� ���� �������� Ȯ���ϴ� ����
    bool bKKeyPressed;

    // JŰ�� ���� �������� Ȯ���ϴ� ����
    bool bJKeyPressed;

    // A,D�� ���� �������� Ȯ���ϴ� ����
    bool bMoveKeyPressed;

    // �޽� ������ �����ִ� �Լ�
    void RotateMesh(bool bIsMovingRight);
    // ���� ������ ��Ÿ�ָ� �������ִ� �Լ� (���� �۵� ����)
    void PlayAnimMontage();

protected:
    virtual void BeginPlay() override;

    // ������Ʈ*************************************
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCameraComponent* Camera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USkeletalMeshComponent* MyMesh;
    // *********************************������Ʈ
    
    // ĳ���� �̵� �ӵ�*********************************
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float WalkSpeed;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float SprintSpeed;
    // *********************************ĳ���� �̵� �ӵ�
    
    // InputSystem ����***********************************
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
    // ************************************** InputSystem ����

     // ���� ��Ÿ�� �Լ� �۵� ���ؼ� �̻�� ����
    UPROPERTY(EditDefaultsOnly, Category = "Montage")
    UAnimMontage* AttackMontage;

    // ���� �浹 ���� ��Ż ������Ʈ
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    APortalActor* OverlapPortal;

    // ���� �浹 ���� ��ٸ� ������Ʈ
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    ALadderActor* OverlapLadder;

    // ĳ���� ����, ���� ��Ÿ�� �Լ� �۵� ���ؼ� �̻�� ����
    ECharacterState State;
    ECharacterAction ActionState;

    // ĳ������ �� �Ʒ� ���� ����� ������Ʈ
    AActor* OverlappingActor;

    // �ִϸ��̼� �������Ʈ���� ����� ����(True�϶� ���� ���)
    bool isGaurd = false;

    // �ִϸ��̼� �������Ʈ���� ����� ����(True�϶� ��ȹ ���)
    bool isCapture;

    // Ű ���� �ð�
    float DownPressTime;
    // Ÿ�̸�
    FTimerHandle DownTimerHandle;
    // Ű �ߺ� �Է� ����
    bool bPushDDownKey = false;

protected:
    // �¿� �̵�
    void Move(const FInputActionValue& Value);
    void MoveEnd();
    // �̵� �ӵ� ����
    void SprintCheck();
    void StartSprint();
    void StopSprint();

    // ���� Ȥ�� ��Ż
    void JumpOrPortalOrLadder(const FInputActionValue& Value);
    // �Ʒ��� �̵� �� �ٴڿ� ����� �� ����Ǵ� �Լ�
    virtual void Landed(const FHitResult& Hit) override;

    // Ű �Է� �ð� ���� ���� �Լ� (�Ʒ� or ���� Ű S�� ���� ������ ȣ��)
    void DownPressed();
    // Ű �Է� ���� �ð� ���� �Լ� (�Ʒ� or ���� Ű S�� ���� ���� ȣ��)
    void DownReleased();
    // �Ʒ��� �̵�
    void Down();
    // ���� �ִϸ��̼� ���� �Լ�
    void Gaurd();
    
    // Ű �Է� �ð� ���� ���� �Լ� (J Ű�� ���� ������ ȣ��)
    void AttackPressed();
    // Ű �Է� ���� �ð� ���� �Լ� (J Ű�� ���� ���� ȣ��)
    void AttackReleased();
    // ���� : ���� �۵� ����
    void Attack();
    // Ŀ�ǵ带 �̿��� ����
    void CommandAttack();
    // ��ȹ �ִϸ��̼� ���� �Լ�
    void Capture();

    // Ư�� Ŀ�ǵ� 1 : K
    void SpecialCommand_1(const FInputActionValue& Value);
    void SpecialCommand_1_Pressed();
    void SpecialCommand_1_Released();
    void HoveringDown();
    
    // Ư�� Ŀ�ǵ� 2 : J
    void SpecialCommand_2();

    // ����
    void Transform();
    // ���� ����
    void UndoTransform();

public:
    AMyCharacter();

    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


    // ��Ż�� ������ �� ���� ��Ż �����͸� ����
    void SetOverlapPortal(APortalActor* Overlap_Portal) { OverlapPortal = Overlap_Portal; }
    // ��ٸ��� ������ �� ���� ��ٸ� �����͸� ����
    void SetOverlapLadder(ALadderActor* Overlap_Ladder) { OverlapLadder = Overlap_Ladder; }
    // ĳ���� ���¸� Flying���� ��ȯ
    void SetLadderStartState();
    // ĳ���� ���¸� Walking���� ��ȯ
    void SetLadderEndState();

    void Forword(const FInputActionValue& Value);
};