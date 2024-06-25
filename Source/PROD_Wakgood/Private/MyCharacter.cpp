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

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(GetRootComponent());
    SpringArm->TargetArmLength = 300.0f;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

    MyMesh = GetMesh();
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
    }
}