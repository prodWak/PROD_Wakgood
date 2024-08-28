#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"

AMyCharacter::AMyCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // ������ �ϰ� ī�޶� ������Ʈ ���� �� ����
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(GetRootComponent());
    SpringArm->TargetArmLength = 300.0f;
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

    // �⺻ �޽� ����
    MyMesh = GetMesh();

    // �⺻ �̵� �ӵ� ����
    WalkSpeed = 600.0f;
    SprintSpeed = 1200.0f;

    // �ʱ� ���� ����
    State = ECharacterState::NONE;
    ActionState = ECharacterAction::IDLE;

    // �浹 ���� ��Ż ����(null������ �ʱ�ȭ)
    OverlapPortal = nullptr;

    // �浹 ���� ��ٸ� ����(null������ �ʱ�ȭ)
    OverlapLadder = nullptr;

    // ���� ĳ���Ϳ� �浹 ���� ������Ʈ(�Ʒ��� �̵� �� ���)
    OverlappingActor = nullptr;

    // ���� �������� ��������(�ߺ� �϶� ����)
    bFalling = false;
    // ���� KŰ�� ���� ��������
    bKKeyPressed = false;
    // ���� JŰ�� ���� ��������
    bJKeyPressed = false;
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();

    // GetController()�� ���� AController�� APlayerController�� ����ȯ
    // APlayerControllerŸ���� �ַ� �÷��̾ ������ ĳ���Ϳ� ����
    // -> ��Ʈ�ѷ�(AController �Ǵ� �� �Ļ� Ŭ����)�� �÷��̾�� ���õ� ���� ���� ������ �����Ѵ�
    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        // EnhancedInput�÷������� ����ؼ� Ű �Է��� �����ϹǷ� �ش� ���� ����
        UEnhancedInputLocalPlayerSubsystem* EnhancedInputSystem;

        // ���� �÷��̾��� ��Ʈ�ѷ����� ���� �÷��̾ ���� �� ���� �÷��̾� ��ü���� EnhancedInputSubSyetem�� ���� ���� �ý��� ��ü�� ��ȯ�ϴ� ��
        // ULocalPlayer : ����ý��� Ÿ���� �޾ƿ����� �ʿ��� ���� (����� EnhancedInputSubSyetem�� �޾ƿ����� ��)
        // PlayerController�� ���� ���� ���� ���� �÷��̾��� ���� �÷��̾� ��ü�� ������ �� �ִ�
        // -> �̸� ���� �Է� ó��, ���� ����, ����ý��� ���� ���� �۾��� ������ �� �ִ�.
        EnhancedInputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

        // EnhancedInputSystem ��ü�� ��ȿ�ϸ�, ���� ���ؽ�Ʈ(MappingContext)�� �߰�
        if (EnhancedInputSystem != nullptr)
        {
            // MappingContext�� �Է� Ű�� ���� �׼� ���� ������ ��� ������, 0�� ���� ���ؽ�Ʈ�� �켱 ������ ��Ÿ���� ��
            EnhancedInputSystem->AddMappingContext(MappingContext, 0);
        }
    }
    // �� ������ �����ؾ� �������Ʈ���� InputMappingConetext�� �������� �� �ִ�. (���ϸ� �������Ʈ���� �����ص� �� ������)
}

// a,dŰ : Move ���� �Լ� ���� ------------------------------------------------------------------------------
void AMyCharacter::Move(const FInputActionValue& Value)// �Է� �׼ǿ� ���� ���� ������ Value�� ���´�.
{
    if (GetController() != nullptr)
    {
        const FVector2D Vector2D = Value.Get<FVector2D>();
        FVector Right = GetActorRightVector();
        if (Vector2D.X != 0)
        {
            bool bIsMovingRight = Vector2D.X > 0;
            RotateMesh(bIsMovingRight);
        }
        AddMovementInput(Right, Vector2D.X);
        //float CurrentTime = GetWorld()->GetTimeSeconds();
        //if (CurrentTime - LastKeyPressTime < DoubleClickTimeThreshold && LastKeyPressTime > 0.0f)
        //{
        //    StartSprint();
        //    FString DebugText = FString::Printf(TEXT("run!!"));
        //    if (GEngine)
        //    {
        //        GEngine->AddOnScreenDebugMessage(21, 1.0f, FColor::Yellow, DebugText);
        //    }
        //}
        //LastKeyPressTime = CurrentTime;
        // ĳ���� ��ǥ �̵�
    }
}

void AMyCharacter::MoveEnd()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Blue, "Key Released : A or D");
    }
    // a + a Ŀ�ǵ� ���� �� �޸��� ������ ���� �Լ� ȣ��
    //StopSprint();
}

void AMyCharacter::RotateMesh(bool bIsMovingRight)
{
    // ���� �޽��� ȸ�� ���¸� ������
    FRotator NewRotation = MyMesh->GetComponentRotation();
    // True ��, �̵� ������ �������� ���, ���������� ���ϰ� Yaw�� 0.0���� �ʱ�ȭ
    if (bIsMovingRight)
    {
        NewRotation.Yaw = 0.0f;
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Blue, "Key Pressed : D");
        }
    }
    // True ��, �̵� ������ ������ ���, �������� ���ϰ� Yaw�� 180�� Ʋ����
    else
    {
        NewRotation.Yaw = 180.0f;
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(3, 1.0f, FColor::Blue, "Key Pressed : A");
        }
    }
    // SetWorldRotation() : ������Ʈ�� ��ġ�� ���� ���������� �������� ȸ�� ������ ����
    MyMesh->SetWorldRotation(NewRotation);
}
// ------------------------------------------------------------------------------a,dŰ : Move ���� �Լ� ��


// ShiftŰ : �޸��� �Լ� ���� ----------------------------------------------------------------------------
void AMyCharacter::StartSprint()
{
    //  GetCharacterMovement() : ACharacter Ŭ������ ��� �Լ���, ĳ������ CharacterMovementComponent�� ���� �����͸� ��ȯ
    //  MaxWalkSpeed : CharacterMovementComponent Ŭ������ ��� ����

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(4, 1.0f, FColor::Blue, "Key Hold : Shift");
    }

    GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AMyCharacter::StopSprint()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(5, 1.0f, FColor::Blue, "Key Released : Shift");
    }

    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}
// ---------------------------------------------------------------------------- ShiftŰ : �޸��� �Լ� ��


// WŰ : ���� ���� �Լ� ���� ----------------------------------------------------------------------------------------
void AMyCharacter::JumpOrPortalOrLadder(const FInputActionValue& Value)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(6, 1.0f, FColor::Blue, "Key Pressed : W");
    }
    if (GetCharacterMovement()->MovementMode == MOVE_Flying)
    {
        // ȣ���� ��� (���� �̵�)
        AddMovementInput(GetActorUpVector(), 10.0f);
    }
    // ������ �� ��Ż ������ �޾ƿ���
    APortalActor* Portal = Cast<APortalActor>(OverlapPortal);
    // ������ �� ��ٸ� ������ �޾Ƶ���
    ALadderActor* Ladder = Cast<ALadderActor>(OverlapLadder);

    if (Portal != nullptr)
    {
        // ���� ������ �� ��Ż�� ���� �� PortalAoctr �Լ� ȣ��
        Portal->Entry();
    }
    else if (Ladder != nullptr)
    {
        // ���� ������ �� ��ٸ��� ���� �� ĳ���� ��ǥ�� ���� �̵�
        AddMovementInput(GetActorUpVector(), Value.Get<FVector2D>().X);
    }
    else
    {
        // ���� ������ �� ��Ż�� ���� �� Jump�Լ� ����
        Jump();
    }
}

void AMyCharacter::SetLadderStartState()
{
    // LadderActor���� �Լ� ȣ�� ���Ѽ� ���� ��ȯ
    GetCharacterMovement()->SetMovementMode(MOVE_Flying);
}
void AMyCharacter::SetLadderEndState()
{
    // LadderActor���� �Լ� ȣ�� ���Ѽ� ���� ��ȯ
    GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}
// ---------------------------------------------------------------------------------------- WŰ : ���� ���� �Լ� ��


// JŰ : Attack ���� �Լ� ���� ----------------------------------------------------------------------------------------
void AMyCharacter::AttackPressed()
{
    if (bPushDDownKey)
        return;
    // AttackAction�� ���� �ð� ���
    DownPressTime = GetWorld()->GetTimeSeconds();

    // 1�� �Ŀ� Capture �Լ��� ȣ���ϵ��� Ÿ�̸� ����
    GetWorldTimerManager().SetTimer(DownTimerHandle, this, &AMyCharacter::Capture, 1.0f, false);
    bPushDDownKey = true;
}

void AMyCharacter::AttackReleased()
{
    // ���� �ð� ���
    float CurrentTime = GetWorld()->GetTimeSeconds();

    GetWorldTimerManager().ClearTimer(DownTimerHandle);

    // Attack �׼��� 1�� �̻� ���ȴ��� Ȯ��
    if (CurrentTime - DownPressTime < 1.0f)
    {
        // Attack �׼��� 1�� �̸����� ���� ���, ���� ���� ����
        //Attack();
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(7, 1.0f, FColor::Blue, "Key Pressed : J(Attack)");
        }
    }

    // Ÿ�̸� �ڵ� �ʱ�ȭ
    DownTimerHandle.Invalidate();
    bPushDDownKey = false;
    isCapture = false;
    bJKeyPressed = false;

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(8, 1.0f, FColor::Blue, "Key Released : J");
    }
}

void AMyCharacter::Attack()
{
    // Attack �ִϸ��̼� ����ǰ� �ϱ�
}

void AMyCharacter::CommandAttack()
{
    bJKeyPressed = true;

    if (bKKeyPressed == true)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(9, 1.0f, FColor::Blue, "Key Pressed : K + J(Jump Attack Command)");
        }
    }
}
void AMyCharacter::Capture()
{
    // ���� Ȱ��ȭ
    isCapture = true;
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(10, 1.0f, FColor::Blue, "Key Hold : J(Capture)");
    }
}
//  --------------------------------------------------------------------------------------------- JŰ : Attack ���� �Լ� ��


void AMyCharacter::Transform()
{
    FString DebugText = FString::Printf(TEXT("Transform!!"));

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(3, 0.1f, FColor::Blue, DebugText);
    }
}

void AMyCharacter::UndoTransform()
{
    FString DebugText = FString::Printf(TEXT("UndoTransform!!"));

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(4, 0.1f, FColor::Blue, DebugText);
    }
}


// KŰ : Ư�� Ŀ��ũ 1 ���� �Լ� ���� ----------------------------------------------------------------------------------------
void AMyCharacter::SpecialCommand_1(const FInputActionValue& Value)
{
    bKKeyPressed = true;
}

void AMyCharacter::SpecialCommand_1_Pressed()
{
    // ȣ���� Ȱ��ȭ
    if (GetCharacterMovement()->IsFalling())
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(11, 1.0f, FColor::Blue, "Key Pressed : K (Special Command 1)");
        }
        GetCharacterMovement()->SetMovementMode(MOVE_Flying);
    }
}

void AMyCharacter::SpecialCommand_1_Released()
{
    // ȣ���� ��Ȱ��ȭ
    if (GetCharacterMovement()->MovementMode == MOVE_Flying)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(11, 1.0f, FColor::Blue, "Key Released : K (Special Command 1)");
        }
        GetCharacterMovement()->SetMovementMode(MOVE_Walking);
    }
    bKKeyPressed = false;
}
//---------------------------------------------------------------------------------------- KŰ : Ư�� Ŀ��ũ 1 ���� �Լ� ��


void AMyCharacter::SpecialCommand_2()
{
    FString DebugText = FString::Printf(TEXT("SpeicalCommand_2"));

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(6, 0.1f, FColor::Blue, DebugText);
    }
}


void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    // ���� ��� ���� �Է� �ý����� EnhnacedInputSubSystem���� Ȯ���ϴ� ����
    // CastChecked�� ����Ͽ� ���� �Է� �ý����� Enhanced�̸� ����, �ƴϸ� ������ ����.
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // MoveAction�� �������Ʈ���� IA_Move��� �������� �Է� �ý����� ���� �Ǿ� �ְ�, �� �� IA_Move�� ���ε� ���� �ԷµǸ� Move�Լ��� ����
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move); // A, D
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AMyCharacter::MoveEnd); // A, D
        EnhancedInputComponent->BindAction(JumpOrPortalAction, ETriggerEvent::Triggered, this, &AMyCharacter::JumpOrPortalOrLadder); // W
        EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &AMyCharacter::StartSprint); // Shift
        EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &AMyCharacter::StopSprint); // Shift
        EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AMyCharacter::AttackPressed); // J
        EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed, this, &AMyCharacter::AttackReleased); // J
        EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AMyCharacter::CommandAttack); // J
        EnhancedInputComponent->BindAction(DownAction, ETriggerEvent::Started, this, &AMyCharacter::DownPressed); // S
        EnhancedInputComponent->BindAction(DownAction, ETriggerEvent::Completed, this, &AMyCharacter::DownReleased); // S
        EnhancedInputComponent->BindAction(DownAction, ETriggerEvent::Triggered, this, &AMyCharacter::HoveringDown); // S

        EnhancedInputComponent->BindAction(TransformAction, ETriggerEvent::Triggered, this, &AMyCharacter::Transform); // Space
        EnhancedInputComponent->BindAction(UndoTransformAction, ETriggerEvent::Triggered, this, &AMyCharacter::UndoTransform); // M
        EnhancedInputComponent->BindAction(SpecialCommandAction_1, ETriggerEvent::Started, this, &AMyCharacter::SpecialCommand_1_Pressed); // K
        EnhancedInputComponent->BindAction(SpecialCommandAction_1, ETriggerEvent::Completed, this, &AMyCharacter::SpecialCommand_1_Released); // K
        EnhancedInputComponent->BindAction(SpecialCommandAction_1, ETriggerEvent::Triggered, this, &AMyCharacter::SpecialCommand_1); // K
        EnhancedInputComponent->BindAction(SpecialCommandAction_2, ETriggerEvent::Triggered, this, &AMyCharacter::SpecialCommand_2); // L
    }
}


// SŰ : �ٿ� ���� �Լ� ���� ---------------------------------------------------------------------------- 
void AMyCharacter::DownPressed()
{
    if (GetCharacterMovement()->MovementMode == MOVE_Walking)
    {
        if (bPushDDownKey)
            return;
        // DownAction�� ���� �ð� ���
        DownPressTime = GetWorld()->GetTimeSeconds();

        // 1�� �Ŀ� EndDown �Լ��� ȣ���ϵ��� Ÿ�̸� ����
        GetWorldTimerManager().SetTimer(DownTimerHandle, this, &AMyCharacter::Gaurd, 1.0f, false);
        bPushDDownKey = true;
    }
}

void AMyCharacter::DownReleased()
{
    // ���� �ð� ���
    float CurrentTime = GetWorld()->GetTimeSeconds();

    GetWorldTimerManager().ClearTimer(DownTimerHandle);

    // Down �׼��� 1�� �̻� ���ȴ��� Ȯ��
    if (CurrentTime - DownPressTime < 1.0f)
    {
        // Down �׼��� 1�� �̸����� ���� ���, ���� ���� ����
        Down();
    }

    // Ÿ�̸� �ڵ� �ʱ�ȭ
    DownTimerHandle.Invalidate();
    bPushDDownKey = false;
    isGaurd = false;
}

void AMyCharacter::Down()
{
    if (bJKeyPressed == true) // �� ���� ������ J + S �ϸ� �Ʒ��� ������
        return;
    // �������� ���̶�� Down ����(�ߺ� �߶� ����)
    if (bFalling)
        return;
    bFalling = true;
    FVector Start = GetActorLocation();
    FVector End = Start + FVector(0.0f, 0.0f, -1000.0f); // �� �Ʒ��� ���� Ʈ���̽�

    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this); // �ڱ� �ڽ��� ����

    // ���� Ʈ���̽� ����
    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);

    if (bHit)
    {
        OverlappingActor = HitResult.GetActor();
        if (OverlappingActor)
        {
            // �������ε� ������ �浹�� ����
            OverlappingActor->SetActorEnableCollision(false);

            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(12, 1.0f, FColor::Blue, "Key Pressed : S (Down)");
            }
            /* if (GEngine)
            {
                FString DebugText = FString::Printf(TEXT("Ignoring Collision with: %s"), *OverlappingActor->GetName());
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DebugText);
            }*/
        }
    }

    // Trace ����� ���� �׸���
    DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.0f, 0, 5.0f);
}

void AMyCharacter::HoveringDown() // ȣ���� �� �Ʒ��� �������� ���
{
    if (bJKeyPressed == true)
    {
        FString DebugText = FString::Printf(TEXT("Capture and Transform"));
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(13, 1.0f, FColor::Blue, "Key Pressed : J + S (Capture and Transform)");
        }
    }
    else if (GetCharacterMovement()->MovementMode == MOVE_Flying)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(14, 1.0f, FColor::Blue, "Key Pressed : S (Hovering Down)");
        }
        AddMovementInput(GetActorUpVector(), -10.0f);
    }
}

// ���� �������� �ڵ����� ���� �Ǵ� �Լ�
void AMyCharacter::Landed(const FHitResult& Hit)
{
    Super::Landed(Hit);

    // ȣ���� ��� ���� �� �߷� ����
    GetCharacterMovement()->GravityScale = 1.0f;

    // ������ �� �浹 Ȱ��ȭ
    if (OverlappingActor)
    {
        // �浹 ���� ó���� �� ������Ʈ �ٽ� �浹 Ȱ��ȭ
        OverlappingActor->SetActorEnableCollision(true);

       /* if (GEngine)
        {
            FString DebugText = FString::Printf(TEXT("Re-enabling Collision with: %s"), *OverlappingActor->GetName());
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, DebugText);
        }*/

        // OverlappingActor�� �ٽ� nullptr�� �����Ͽ� ���� ȣ�� �ÿ� ������ ���� �ʵ��� ��
        OverlappingActor = nullptr;
    }

    bFalling = false;
}

void AMyCharacter::Gaurd()
{
    // ���� Ȱ��ȭ
    isGaurd = true;
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(14, 1.0f, FColor::Blue, "Key Hold : S (Gaurd)");
    }
}
// ---------------------------------------------------------------------------- SŰ : �ٿ� ���� �Լ� ��

void AMyCharacter::PlayAnimMontage()
{
    if (AttackMontage == nullptr)
        return;

    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    if (AnimInstance != nullptr)
    {
        AnimInstance->Montage_JumpToSection(FName("Attack1"), AttackMontage);
        AnimInstance->Montage_Play(AttackMontage);
    }
}