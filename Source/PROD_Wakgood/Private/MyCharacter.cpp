#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
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

    // ���� ĳ���Ϳ� �浹 ���� ������Ʈ(�Ʒ��� �̵� �� ���)
    OverlappingActor = nullptr;

    // ���� �������� ��������(�ߺ� �϶� ����)
    bFalling = false;
}

// Called when the game starts or when spawned
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

// �Է� �׼ǿ� ���� ���� ������ Value�� ���´�.
void AMyCharacter::Move(const FInputActionValue& Value)
{
    if (ActionState == ECharacterAction::ATTACK)
        return;
    // �÷��̾� ��Ʈ�ѷ��� ������ ��
    if (GetController() != nullptr)
    {
        // Value��ü���� FVector2D Ÿ���� ������ ����(2���� ���� : x,y)
        // �� �����Ϳ��� �¿�θ� �̵��� ���̹Ƿ� X�� ����Ѵ�.
        const FVector2D Vector2D = Value.Get<FVector2D>();

        // GetActorRightVector() : ���Ͱ� ���� ���ϰ� �ִ� ������ �������� ��Ÿ���� ���͸� ��ȯ
        FVector Right = GetActorRightVector();

        // �̵� ���⿡ ���� �޽� ȸ��(�̵� ���� 0�� �ƴ� ��)
        if (Vector2D.X != 0)
        {
            bool bIsMovingRight = Vector2D.X > 0;
            // �̵� ������ �������̸� true, �����̸� false(�޽��� ȸ���� ���)
            RotateMesh(bIsMovingRight);
        }
        // Right(���� ���� �ٶ󺸰� �ִ� ����) �������� Vector2D.X(���� �Էµ� ���� ��)��ŭ �̵�
        AddMovementInput(Right, Vector2D.X);
    }
}

void AMyCharacter::RotateMesh(bool bIsMovingRight)
{
    // ���� �޽��� ȸ�� ���¸� ������
    FRotator NewRotation = MyMesh->GetComponentRotation();
    // True ��, �̵� ������ �������� ���, ���������� ���ϰ� Yaw�� 0.0���� �ʱ�ȭ
    if (bIsMovingRight)
    {
        NewRotation.Yaw = 0.0f;
    }
    // True ��, �̵� ������ ������ ���, �������� ���ϰ� Yaw�� 180�� Ʋ����
    else
    {
        NewRotation.Yaw = 180.0f;
    }
    // SetWorldRotation() : ������Ʈ�� ��ġ�� ���� ���������� �������� ȸ�� ������ ����
    MyMesh->SetWorldRotation(NewRotation);
}

void AMyCharacter::StartSprint()
{
    //  GetCharacterMovement() : ACharacter Ŭ������ ��� �Լ���, ĳ������ CharacterMovementComponent�� ���� �����͸� ��ȯ
    //  MaxWalkSpeed : CharacterMovementComponent Ŭ������ ��� ����
    GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AMyCharacter::StopSprint()
{
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AMyCharacter::JumpOrPortal()
{
    // ������ �� ��Ż ������ �޾ƿ���
    APortalActor* Portal = Cast<APortalActor>(OverlapPortal);
    if (Portal != nullptr)
    {
        // ���� ������ �� ��Ż�� ���� �� PortalAoctr �Լ� ȣ��
        Portal->Entry();
    }
    else
    {
        // ���� ������ �� ��Ż�� ���� �� Jump�Լ� ����
        Jump();
    }
}

void AMyCharacter::Down()
{
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

            // **************����� �ڵ� ����
            if (GEngine)
            {
                FString DebugText = FString::Printf(TEXT("Ignoring Collision with: %s"), *OverlappingActor->GetName());
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DebugText);
            }
            //����� �ڵ� �� *************** 
        }
    }

    // Trace ����� ���� �׸���
    DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.0f, 0, 5.0f);
}

// ���� �������� �ڵ����� ���� �Ǵ� �Լ�
void AMyCharacter::Landed(const FHitResult& Hit)
{
    Super::Landed(Hit);

    // ������ �� �浹 Ȱ��ȭ
    if (OverlappingActor)
    {
        // �浹 ���� ó���� �� ������Ʈ �ٽ� �浹 Ȱ��ȭ
        OverlappingActor->SetActorEnableCollision(true);

        // ����� �޽��� �߰�
        if (GEngine)
        {
            FString DebugText = FString::Printf(TEXT("Re-enabling Collision with: %s"), *OverlappingActor->GetName());
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, DebugText);
        }

        // OverlappingActor�� �ٽ� nullptr�� �����Ͽ� ���� ȣ�� �ÿ� ������ ���� �ʵ��� ��
        OverlappingActor = nullptr;
    }

    bFalling = false;
}

void AMyCharacter::Attack(const FInputActionValue& value)
{
    if (ActionState == ECharacterAction::ATTACK || State != ECharacterState::ONE_HAND_GUN)
        return;

    PlayAnimMontage();
    ActionState = ECharacterAction::ATTACK;
}

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

void AMyCharacter::SpecialCommand_1()
{
    FString DebugText = FString::Printf(TEXT("SpeicalCommand_1"));

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(5, 0.1f, FColor::Blue, DebugText);
    }
}

void AMyCharacter::SpecialCommand_2()
{
    FString DebugText = FString::Printf(TEXT("SpeicalCommand_2"));

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(6, 0.1f, FColor::Blue, DebugText);
    }
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    // ���� ��� ���� �Է� �ý����� EnhnacedInputSubSystem���� Ȯ���ϴ� ����
    // CastChecked�� ����Ͽ� ���� �Է� �ý����� Enhanced�̸� ����, �ƴϸ� ������ ����.
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // MoveAction�� �������Ʈ���� IA_Move��� �������� �Է� �ý����� ���� �Ǿ� �ְ�, �� �� IA_Move�� ���ε� ���� �ԷµǸ� Move�Լ��� ����
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
        EnhancedInputComponent->BindAction(JumpOrPortalAction, ETriggerEvent::Triggered, this, &AMyCharacter::JumpOrPortal);
        EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &AMyCharacter::StartSprint);
        EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &AMyCharacter::StopSprint);
        EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AMyCharacter::Attack);
        EnhancedInputComponent->BindAction(DownAction, ETriggerEvent::Started, this, &AMyCharacter::StartDown);
        EnhancedInputComponent->BindAction(DownAction, ETriggerEvent::Completed, this, &AMyCharacter::EndDown);

        EnhancedInputComponent->BindAction(TransformAction, ETriggerEvent::Triggered, this, &AMyCharacter::Transform);
        EnhancedInputComponent->BindAction(UndoTransformAction, ETriggerEvent::Triggered, this, &AMyCharacter::UndoTransform);
        EnhancedInputComponent->BindAction(SpecialCommandAction_1, ETriggerEvent::Triggered, this, &AMyCharacter::SpecialCommand_1);
        EnhancedInputComponent->BindAction(SpecialCommandAction_2, ETriggerEvent::Triggered, this, &AMyCharacter::SpecialCommand_2);
    }
}

void AMyCharacter::StartDown(const FInputActionValue& Value)
{
    if (bPushDDownKey)
        return;
    // DownAction�� ���� �ð� ���
    DownPressTime = GetWorld()->GetTimeSeconds();

    // 1�� �Ŀ� EndDown �Լ��� ȣ���ϵ��� Ÿ�̸� ����
    GetWorldTimerManager().SetTimer(DownTimerHandle, this, &AMyCharacter::Gaurd, 1.0f, false);
    bPushDDownKey = true;
}

void AMyCharacter::EndDown()
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

void AMyCharacter::Gaurd()
{
    // ���� Ȱ��ȭ
    isGaurd = true;
    FString DebugText = FString::Printf(TEXT("Gaurd!"));
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(28, 1.0f, FColor::Yellow, DebugText);
    }
}

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