#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PortalActor.h"
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

UCLASS()
class PROD_WAKGOOD_API AMyCharacter : public ACharacter
{
    GENERATED_BODY()

private:

    // ���� �������� �� = true
    bool bFalling;

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
    
    // ĳ���� �̵� �ӵ�
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float WalkSpeed;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float SprintSpeed;

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


    UPROPERTY(EditDefaultsOnly, Category = "Montage")
    UAnimMontage* AttackMontage; // ���� ��Ÿ�� �Լ� �۵� ���ؼ� �̻�� ����

    // ���� �浹 ���� ��Ż ������Ʈ
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    APortalActor* OverlapPortal;

    // ĳ���� ����, ���� ��Ÿ�� �Լ� �۵� ���ؼ� �̻�� ����
    ECharacterState State;
    ECharacterAction ActionState;

    // ĳ������ �� �Ʒ� ���� ����� ������Ʈ
    AActor* OverlappingActor;

protected:
    // �¿� �̵�
    void Move(const FInputActionValue& Value);

    // �̵� �ӵ� ����
    void StartSprint();
    void StopSprint();

    // ���� Ȥ�� ��Ż
    void JumpOrPortal();

    // �Ʒ��� �̵�
    void Down();

    // �Ʒ��� �̵� �� �ٴڿ� ����� �� ����Ǵ� �Լ�
    virtual void Landed(const FHitResult& Hit) override;

    // ���� : ���� �۵� ���� -> ���� �κ� ��������ͷ� ó��
    void Attack(const FInputActionValue& Value);

    // ����
    void Transform();
    // ���� ����
    void UndoTransform();
    // Ư�� Ŀ�ǵ� 1
    void SpecialCommand_1();
    // Ư�� Ŀ�ǵ� 2
    void SpecialCommand_2();

public:
    AMyCharacter();

    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // PortalAcotr���� ��� ���� public
    void SetOverlapPortal(APortalActor* Overlap_Portal) { OverlapPortal = Overlap_Portal; }

    // Ű �Է� �ð� ���� ���� �Լ� (�Ʒ� or ���� Ű S�� ���� ������ ȣ��)
    void StartDown(const FInputActionValue& Value);
    // Ű �Է� ���� �ð� ���� �Լ� (�Ʒ� or ���� Ű S�� ���� ���� ȣ��)
    void EndDown();
    // SŰ ���� �ð�
    float DownPressTime;
    // Ÿ�̸�
    FTimerHandle DownTimerHandle;
    // Ű �ߺ� �Է� ����
    bool bPushDDownKey = false;
    // ���� �ִϸ��̼� ���� �Լ�
    void Gaurd();
    // �ִϸ��̼� �������Ʈ���� ����� ����(True�϶� ���� ���)
    bool isGaurd = false;
};