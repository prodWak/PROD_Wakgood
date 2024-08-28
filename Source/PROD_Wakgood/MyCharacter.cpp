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

    // 스프링 암과 카메라 컴포넌트 생성 및 설정
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(GetRootComponent());
    SpringArm->TargetArmLength = 300.0f;
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

    // 기본 메시 설정
    MyMesh = GetMesh();

    // 기본 이동 속도 설정
    WalkSpeed = 600.0f;
    SprintSpeed = 1200.0f;

    // 초기 상태 설정
    State = ECharacterState::NONE;
    ActionState = ECharacterAction::IDLE;

    // 충돌 중인 포탈 설정(null값으로 초기화)
    OverlapPortal = nullptr;

    // 충돌 중인 사다리 설정(null값으로 초기화)
    OverlapLadder = nullptr;

    // 현재 캐릭터와 충돌 중인 오브젝트(아래로 이동 시 사용)
    OverlappingActor = nullptr;

    // 현재 떨어지는 상태인지(중복 하락 방지)
    bFalling = false;
    // 현재 K키를 누른 상태인지
    bKKeyPressed = false;
    // 현재 J키를 누른 상태인지
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

// a,d키 : Move 관련 함수 시작 ------------------------------------------------------------------------------
void AMyCharacter::Move(const FInputActionValue& Value)// 입력 액션에 대한 상세한 정보가 Value로 들어온다.
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
        // 캐릭터 좌표 이동
    }
}

void AMyCharacter::MoveEnd()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Blue, "Key Released : A or D");
    }
    // a + a 커맨드 끝날 시 달리기 끝내기 위한 함수 호출
    //StopSprint();
}

void AMyCharacter::RotateMesh(bool bIsMovingRight)
{
    // 현재 메시의 회전 상태를 가져옴
    FRotator NewRotation = MyMesh->GetComponentRotation();
    // True 즉, 이동 방향이 오른쪽일 경우, 오른쪽으로 향하게 Yaw를 0.0으로 초기화
    if (bIsMovingRight)
    {
        NewRotation.Yaw = 0.0f;
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Blue, "Key Pressed : D");
        }
    }
    // True 즉, 이동 방향이 왼쪽일 경우, 왼쪽으로 향하게 Yaw를 180도 틀어줌
    else
    {
        NewRotation.Yaw = 180.0f;
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(3, 1.0f, FColor::Blue, "Key Pressed : A");
        }
    }
    // SetWorldRotation() : 컴포넌트가 위치한 월드 공간에서의 절대적인 회전 각도를 설정
    MyMesh->SetWorldRotation(NewRotation);
}
// ------------------------------------------------------------------------------a,d키 : Move 관련 함수 끝


// Shift키 : 달리기 함수 시작 ----------------------------------------------------------------------------
void AMyCharacter::StartSprint()
{
    //  GetCharacterMovement() : ACharacter 클래스의 멤버 함수로, 캐릭터의 CharacterMovementComponent에 대한 포인터를 반환
    //  MaxWalkSpeed : CharacterMovementComponent 클래스의 멤버 변수

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
// ---------------------------------------------------------------------------- Shift키 : 달리기 함수 끝


// W키 : 점프 관련 함수 시작 ----------------------------------------------------------------------------------------
void AMyCharacter::JumpOrPortalOrLadder(const FInputActionValue& Value)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(6, 1.0f, FColor::Blue, "Key Pressed : W");
    }
    if (GetCharacterMovement()->MovementMode == MOVE_Flying)
    {
        // 호버링 기능 (위로 이동)
        AddMovementInput(GetActorUpVector(), 10.0f);
    }
    // 오버랩 된 포탈 데이터 받아오기
    APortalActor* Portal = Cast<APortalActor>(OverlapPortal);
    // 오버랩 된 사다리 데이터 받아도기
    ALadderActor* Ladder = Cast<ALadderActor>(OverlapLadder);

    if (Portal != nullptr)
    {
        // 현재 오버랩 된 포탈이 있을 시 PortalAoctr 함수 호출
        Portal->Entry();
    }
    else if (Ladder != nullptr)
    {
        // 현재 오버랩 된 사다리가 있을 시 캐릭터 좌표를 위로 이동
        AddMovementInput(GetActorUpVector(), Value.Get<FVector2D>().X);
    }
    else
    {
        // 현재 오버랩 된 포탈이 없을 시 Jump함수 실행
        Jump();
    }
}

void AMyCharacter::SetLadderStartState()
{
    // LadderActor에서 함수 호출 시켜서 상태 변환
    GetCharacterMovement()->SetMovementMode(MOVE_Flying);
}
void AMyCharacter::SetLadderEndState()
{
    // LadderActor에서 함수 호출 시켜서 상태 변환
    GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}
// ---------------------------------------------------------------------------------------- W키 : 점프 관련 함수 끝


// J키 : Attack 관련 함수 시작 ----------------------------------------------------------------------------------------
void AMyCharacter::AttackPressed()
{
    if (bPushDDownKey)
        return;
    // AttackAction이 눌린 시간 기록
    DownPressTime = GetWorld()->GetTimeSeconds();

    // 1초 후에 Capture 함수를 호출하도록 타이머 설정
    GetWorldTimerManager().SetTimer(DownTimerHandle, this, &AMyCharacter::Capture, 1.0f, false);
    bPushDDownKey = true;
}

void AMyCharacter::AttackReleased()
{
    // 현재 시간 계산
    float CurrentTime = GetWorld()->GetTimeSeconds();

    GetWorldTimerManager().ClearTimer(DownTimerHandle);

    // Attack 액션이 1초 이상 눌렸는지 확인
    if (CurrentTime - DownPressTime < 1.0f)
    {
        // Attack 액션이 1초 미만으로 눌린 경우, 기존 동작 실행
        //Attack();
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(7, 1.0f, FColor::Blue, "Key Pressed : J(Attack)");
        }
    }

    // 타이머 핸들 초기화
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
    // Attack 애니메이션 실행되게 하기
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
    // 가드 활성화
    isCapture = true;
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(10, 1.0f, FColor::Blue, "Key Hold : J(Capture)");
    }
}
//  --------------------------------------------------------------------------------------------- J키 : Attack 관련 함수 끝


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


// K키 : 특수 커맨크 1 관련 함수 시작 ----------------------------------------------------------------------------------------
void AMyCharacter::SpecialCommand_1(const FInputActionValue& Value)
{
    bKKeyPressed = true;
}

void AMyCharacter::SpecialCommand_1_Pressed()
{
    // 호버링 활성화
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
    // 호버링 비활성화
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
//---------------------------------------------------------------------------------------- K키 : 특수 커맨크 1 관련 함수 끝


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
    // 현재 사용 중인 입력 시스템이 EnhnacedInputSubSystem인지 확인하는 과정
    // CastChecked를 사용하여 현재 입력 시스템이 Enhanced이면 실행, 아니면 오류를 띄운다.
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // MoveAction이 블루프린트에서 IA_Move라고 만들어놓은 입력 시스템이 연결 되어 있고, 이 때 IA_Move에 매핑된 값이 입력되면 Move함수가 실행
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


// S키 : 다운 관련 함수 시작 ---------------------------------------------------------------------------- 
void AMyCharacter::DownPressed()
{
    if (GetCharacterMovement()->MovementMode == MOVE_Walking)
    {
        if (bPushDDownKey)
            return;
        // DownAction이 눌린 시간 기록
        DownPressTime = GetWorld()->GetTimeSeconds();

        // 1초 후에 EndDown 함수를 호출하도록 타이머 설정
        GetWorldTimerManager().SetTimer(DownTimerHandle, this, &AMyCharacter::Gaurd, 1.0f, false);
        bPushDDownKey = true;
    }
}

void AMyCharacter::DownReleased()
{
    // 현재 시간 계산
    float CurrentTime = GetWorld()->GetTimeSeconds();

    GetWorldTimerManager().ClearTimer(DownTimerHandle);

    // Down 액션이 1초 이상 눌렸는지 확인
    if (CurrentTime - DownPressTime < 1.0f)
    {
        // Down 액션이 1초 미만으로 눌린 경우, 기존 동작 실행
        Down();
    }

    // 타이머 핸들 초기화
    DownTimerHandle.Invalidate();
    bPushDDownKey = false;
    isGaurd = false;
}

void AMyCharacter::Down()
{
    if (bJKeyPressed == true) // 이 조건 없으면 J + S 하면 아래로 떨어짐
        return;
    // 떨어지는 중이라면 Down 막기(중복 추락 방지)
    if (bFalling)
        return;
    bFalling = true;
    FVector Start = GetActorLocation();
    FVector End = Start + FVector(0.0f, 0.0f, -1000.0f); // 발 아래로 라인 트레이스

    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this); // 자기 자신은 무시

    // 라인 트레이스 수행
    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);

    if (bHit)
    {
        OverlappingActor = HitResult.GetActor();
        if (OverlappingActor)
        {
            // 오버래핑된 액터의 충돌을 무시
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

    // Trace 디버그 라인 그리기
    DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.0f, 0, 5.0f);
}

void AMyCharacter::HoveringDown() // 호버링 중 아래로 떨어지는 기능
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

// 땅에 떨어지면 자동으로 실행 되는 함수
void AMyCharacter::Landed(const FHitResult& Hit)
{
    Super::Landed(Hit);

    // 호버링 기능 수행 후 중력 복구
    GetCharacterMovement()->GravityScale = 1.0f;

    // 떨어진 후 충돌 활성화
    if (OverlappingActor)
    {
        // 충돌 무시 처리해 둔 오브젝트 다시 충돌 활성화
        OverlappingActor->SetActorEnableCollision(true);

       /* if (GEngine)
        {
            FString DebugText = FString::Printf(TEXT("Re-enabling Collision with: %s"), *OverlappingActor->GetName());
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, DebugText);
        }*/

        // OverlappingActor를 다시 nullptr로 설정하여 다음 호출 시에 영향을 주지 않도록 함
        OverlappingActor = nullptr;
    }

    bFalling = false;
}

void AMyCharacter::Gaurd()
{
    // 가드 활성화
    isGaurd = true;
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(14, 1.0f, FColor::Blue, "Key Hold : S (Gaurd)");
    }
}
// ---------------------------------------------------------------------------- S키 : 다운 관련 함수 끝

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