#include "CPlayer.h"
#include "Global.h"

#include "Components/CWeaponComponent.h"
#include "Components/CActionComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Animation/CAnimInstance.h"
#include "Widgets/CWidget_HUD.h"
#include "Attributes/CAttributeSet.h"
#include "Actions/CAction.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"



//  *********************
//      기본 세팅
//  *********************
ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;


	//메쉬 설정
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Characters/Player/Meshes/SK_CyberpunkSamurai_WithHelmet.SK_CyberpunkSamurai_WithHelmet'");
	GetMesh()->SetSkeletalMesh(mesh);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	//카메라 설정
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	SpringArm->SetRelativeLocation(FVector(0, 0, 150));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bDoCollisionTest = false;

	Camera->SetRelativeLocation(FVector(-30, 0, 0));
	Camera->bUsePawnControlRotation = false;

	//애니메이션 설정
	TSubclassOf<UCAnimInstance> animInstance;
	CHelpers::GetClass<UCAnimInstance>(&animInstance, "AnimBlueprint'/Game/Animations/ABP_Character.ABP_Character_C'");
	GetMesh()->SetAnimClass(animInstance);
	

	//HP, MP HUD 클래스 설정
	/* MaxHP = 10000.0f;
	CurrHP = MaxHP;
	MaxMP = 100.0f;
	CurrMP = 0.0f; */
	CHelpers::GetClass<UCWidget_HUD>(&HUDClass, "WidgetBlueprint'/Game/Widgets/WB_HUD.WB_HUD_C'");
	
	

	//캐릭터 기본 설정
	GetCharacterMovement()->MaxWalkSpeed = 400;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	JumpMaxCount = 2;
	JumpMaxHoldTime = 0.5f;

	for(UINT u = 0; u < 4; u++)
		bMoving[u] = false;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	//HUD 설정
	if (!!HUDClass)
	{
		HUD = CreateWidget<UCWidget_HUD, APlayerController>(GetController<APlayerController>(), HUDClass);
		HUD->AddToViewport();
		HUD->SetVisibility(ESlateVisibility::Visible);
		HUD->UpdateHP(GetCurrHP(), GetMaxHP());
		HUD->UpdateMP(GetCurrMP(), GetMaxMP());
	}
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//에너지 게이지 자연 증가
	/* CurrMP += TickMPAmount; */
	//HUD->UpdateMP(GetCurrMP(), GetMaxMP());
}


//  *********************
//      Attribute 처리
//  *********************
float ACPlayer::GetCurrMP() const
{
	if(!!AttributeSet)
		return AttributeSet->GetCurrMP();
	return 0.0f;
}
float ACPlayer::GetMaxMP() const
{
	if(!!AttributeSet)
		return AttributeSet->GetMaxMP();
	return 0.0f;
}


void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//축 인풋 : 이동, 카메라
	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	
	//이동 입력 감지, 더블 탭 시 달리기
	PlayerInputComponent->BindAction("MoveF", IE_Pressed, this, &ACPlayer::PressedMoveF);
	PlayerInputComponent->BindAction("MoveR", IE_Pressed, this, &ACPlayer::PressedMoveB);
	PlayerInputComponent->BindAction("MoveB", IE_Pressed, this, &ACPlayer::PressedMoveL);
	PlayerInputComponent->BindAction("MoveL", IE_Pressed, this, &ACPlayer::PressedMoveR);

	PlayerInputComponent->BindAction("MoveF", IE_Released, this, &ACPlayer::ReleasedMoveF);
	PlayerInputComponent->BindAction("MoveR", IE_Released, this, &ACPlayer::ReleasedMoveB);
	PlayerInputComponent->BindAction("MoveB", IE_Released, this, &ACPlayer::ReleasedMoveL);
	PlayerInputComponent->BindAction("MoveL", IE_Released, this, &ACPlayer::ReleasedMoveR);

	PlayerInputComponent->BindAction("MoveF", IE_DoubleClick, this, &ACPlayer::BeginRunning);
	PlayerInputComponent->BindAction("MoveR", IE_DoubleClick, this, &ACPlayer::BeginRunning);
	PlayerInputComponent->BindAction("MoveB", IE_DoubleClick, this, &ACPlayer::BeginRunning);
	PlayerInputComponent->BindAction("MoveL", IE_DoubleClick, this, &ACPlayer::BeginRunning);
	
	//점프
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACPlayer::PressedJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACPlayer::ReleasedJump);
	
	//회피
	PlayerInputComponent->BindAction("Evade", IE_Pressed, this, &ACPlayer::PressedEvade);
	
	//무기 교체
	PlayerInputComponent->BindAction("Weapon1", IE_Pressed, this, &ACPlayer::ChangeWeapon1);
	PlayerInputComponent->BindAction("Weapon2", IE_Pressed, this, &ACPlayer::ChangeWeapon2);
	PlayerInputComponent->BindAction("Weapon3", IE_Pressed, this, &ACPlayer::ChangeWeapon3);
	PlayerInputComponent->BindAction("Weapon4", IE_Pressed, this, &ACPlayer::ChangeWeapon4);

	//액션 키
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &ACPlayer::PressedAction);
	PlayerInputComponent->BindAction("Action", IE_Released, this, &ACPlayer::ReleasedAction);

	//서브액션 키
	PlayerInputComponent->BindAction("SubAction", IE_Pressed, this, &ACPlayer::PressedSubAction);
	PlayerInputComponent->BindAction("SubAction", IE_Released, this, &ACPlayer::ReleasedSubAction);
}


bool ACPlayer::IsMoving()
{
	return bMoving[0] || bMoving[1] || bMoving[2] || bMoving[3];
}


void ACPlayer::OnMoveForward(float AxisValue)
{
	CheckFalse(StatusComponent->CanMove());
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, AxisValue);
}

void ACPlayer::OnMoveRight(float AxisValue)
{
	CheckFalse(StatusComponent->CanMove());
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, AxisValue);
}

void ACPlayer::OnVerticalLook(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void ACPlayer::OnHorizontalLook(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void ACPlayer::PressedJump()
{
	CheckFalse(StatusComponent->CanAction());
	ActionComponent->OnActionInput.Execute(EActionType::Jump, true);
}

void ACPlayer::ReleasedJump()
{
	ActionComponent->OnActionInput.Execute(EActionType::Jump, false);
}

void ACPlayer::PressedEvade()
{
	CheckFalse(StatusComponent->CanAction());
	ActionComponent->OnActionInput.Execute(EActionType::Dash, true);
}


void ACPlayer::PressedMoveF()
{
	CheckFalse(StatusComponent->CanMove());
	bMoving[0] = true;
}
void ACPlayer::PressedMoveB()
{
	CheckFalse(StatusComponent->CanMove());
	bMoving[1] = true;
}
void ACPlayer::PressedMoveL()
{
	CheckFalse(StatusComponent->CanMove());
	bMoving[2] = true;
}
void ACPlayer::PressedMoveR()
{
	CheckFalse(StatusComponent->CanMove());
	bMoving[3] = true;
}

void ACPlayer::ReleasedMoveF()
{
	CheckFalse(StatusComponent->CanMove());
	bMoving[0] = false;
	if (!IsMoving())
	{
		StateComponent->SetIdleMode();
		GetCharacterMovement()->MaxWalkSpeed = 400;
	}
}
void ACPlayer::ReleasedMoveB()
{
	CheckFalse(StatusComponent->CanMove());
	bMoving[1] = false;
	if (!IsMoving())
	{
		StateComponent->SetIdleMode();
		GetCharacterMovement()->MaxWalkSpeed = 400;
	}
}
void ACPlayer::ReleasedMoveL()
{
	CheckFalse(StatusComponent->CanMove());
	bMoving[2] = false;
	if (!IsMoving())
	{
		StateComponent->SetIdleMode();
		GetCharacterMovement()->MaxWalkSpeed = 400;
	}
}
void ACPlayer::ReleasedMoveR()
{
	CheckFalse(StatusComponent->CanMove());
	bMoving[3] = false;
	if (!IsMoving())
	{
		StateComponent->SetIdleMode();
		GetCharacterMovement()->MaxWalkSpeed = 400;
	}
}

void ACPlayer::BeginRunning()
{
	StateComponent->SetDashMode();
	GetCharacterMovement()->MaxWalkSpeed = 800;
}


//  *********************
//      무기 교체
//  *********************
void ACPlayer::ChangeWeapon1()
{
	CheckFalse(StatusComponent->CanMove());
	ChangeWeapon(1);
}
void ACPlayer::ChangeWeapon2()
{
	CheckFalse(StatusComponent->CanMove());
	ChangeWeapon(2);
}
void ACPlayer::ChangeWeapon3()
{
	CheckFalse(StatusComponent->CanMove());
	ChangeWeapon(3);
}
void ACPlayer::ChangeWeapon4()
{
	CheckFalse(StatusComponent->CanMove());
	ChangeWeapon(4);
}

void ACPlayer::PressedAction()
{
	CheckFalse(StatusComponent->CanAction());
	ActionComponent->OnActionInput.Execute(EActionType::Action, true);
}

void ACPlayer::ReleasedAction()
{
	ActionComponent->OnActionInput.Execute(EActionType::Action, false);
}

void ACPlayer::PressedSubAction()
{
	CheckFalse(StatusComponent->CanAction());
	ActionComponent->OnActionInput.Execute(EActionType::SubAction, true);
}

void ACPlayer::ReleasedSubAction()
{
	ActionComponent->OnActionInput.Execute(EActionType::SubAction, false);
}


void ACPlayer::UseControlRotation()
{
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void ACPlayer::NotUseControlRotation()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
}


//  *********************
//      Equip 처리
//  *********************
void ACPlayer::ChangeWeapon(uint8 const& InNumber)
{
	Super::ChangeWeapon(InNumber);
	CheckNull(WeaponComponent);
	WeaponComponent->ChangeWeapon(InNumber);
}
