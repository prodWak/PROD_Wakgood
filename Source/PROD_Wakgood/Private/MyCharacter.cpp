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

    // GetController()로 받은 AController를 APlayerController로 형변환
    // APlayerController타입은 주로 플레이어가 조종할 캐릭터에 적용
    // -> 컨트롤러(AController 또는 그 파생 클래스)는 플레이어와 관련된 여러 가지 정보를 포함한다
    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        // EnhancedInput플러그인을 사용해서 키 입력을 매핑하므로 해당 변수 선언
        UEnhancedInputLocalPlayerSubsystem* EnhancedInputSystem;

        // 현재 플레이어의 컨트롤러에서 로컬 플레이어를 얻어와 그 로컬 플레이어 객체에서 EnhancedInputSubSyetem의 로컬 서브 시스템 객체를 반환하는 것
        // ULocalPlayer : 서브시스템 타입을 받아오려면 필요한 선언 (현재는 EnhancedInputSubSyetem을 받아오려는 것)
        // PlayerController를 통해 현재 조작 중인 플레이어의 로컬 플레이어 객체를 가져올 수 있다
        // -> 이를 통해 입력 처리, 설정 관리, 서브시스템 접근 등의 작업을 수행할 수 있다.
        EnhancedInputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

        // EnhancedInputSystem 객체가 유효하면, 매핑 컨텍스트(MappingContext)를 추가
        if (EnhancedInputSystem != nullptr)
        {
            // MappingContext는 입력 키와 게임 액션 매핑 설정을 담고 있으며, 0은 매핑 컨텍스트의 우선 순위를 나타내는 값
            EnhancedInputSystem->AddMappingContext(MappingContext, 0);
        }
    }
    // 이 과정을 진행해야 블루프린트에서 InputMappingConetext를 연결해줄 수 있다. (안하면 블루프린트에서 연결해도 안 움직임)
}

// 입력 액션에 대한 상세한 정보가 Value로 들어온다.
void AMyCharacter::Move(const FInputActionValue& Value)
{
    // 플레이어 컨트롤러가 존재할 때
    if (GetController() != nullptr)
    {
        // Value객체에서 FVector2D 타입의 데이터 추출(2차원 벡터 : x,y)
        // 이 데이터에서 좌우로만 이동할 것이므로 X만 사용한다.
        const FVector2D Vector2D = Value.Get<FVector2D>();

        // GetActorRightVector() : 액터가 현재 향하고 있는 방향의 오른쪽을 나타내는 벡터를 반환
        FVector Right = GetActorRightVector();

        // 이동 방향에 따라 메쉬 회전(이동 값이 0이 아닐 때)
        if (Vector2D.X != 0)
        {
            bool bIsMovingRight = Vector2D.X > 0;
            // 이동 방향이 오른쪽이면 true, 왼쪽이면 false(메시의 회전에 사용)
            RotateMesh(bIsMovingRight);
        }
        // Right(현재 내가 바라보고 있는 방향) 방향으로 Vector2D.X(현재 입력된 벡터 값)만큼 이동
        AddMovementInput(Right, Vector2D.X);
    }
}

void AMyCharacter::RotateMesh(bool bIsMovingRight)
{
    // 현재 메시의 회전 상태를 가져옴
    FRotator NewRotation = MyMesh->GetComponentRotation();
    // True 즉, 이동 방향이 오른쪽일 경우, 오른쪽으로 향하게 Yaw를 0.0으로 초기화
    if (bIsMovingRight)
    {
        NewRotation.Yaw = 0.0f;
    }
    // True 즉, 이동 방향이 왼쪽일 경우, 왼쪽으로 향하게 Yaw를 180도 틀어줌
    else
    {
        NewRotation.Yaw = 180.0f;
    }
    // SetWorldRotation() : 컴포넌트가 위치한 월드 공간에서의 절대적인 회전 각도를 설정
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
    // 현재 사용 중인 입력 시스템이 EnhnacedInputSubSystem인지 확인하는 과정
    // CastChecked를 사용하여 현재 입력 시스템이 Enhanced이면 실행, 아니면 오류를 띄운다.
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // MoveAction이 블루프린트에서 IA_Move라고 만들어놓은 입력 시스템이 연결 되어 있고, 이 때 IA_Move에 매핑된 값이 입력되면 Move함수가 실행
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
    }
}