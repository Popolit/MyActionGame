#include "CPlayer.h"
#include "CHelpers.h"

#include "Components/CWeaponComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Widgets/CWidget_HUD.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CActionComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"


ACPlayer::ACPlayer() : ACCharacter_Base(), bMoving{ false, false, false, false }
{
	PrimaryActorTick.bCanEverTick = false;

	//ī�޶� ����
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	SpringArm->SetRelativeLocation(FVector(0, 0, 150));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bDoCollisionTest = false;

	Camera->SetRelativeLocation(FVector(-30, 0, 0));
	Camera->bUsePawnControlRotation = false;

	//ĳ���� �⺻ ���� ����
	GetCharacterMovement()->MaxWalkSpeed = StatusComponent->GetWalkSpeed();
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	JumpMaxCount = 2;
	JumpMaxHoldTime = 0.5f;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	//HUD ����
	if (!!HUDClass)
	{
		HUD = CreateWidget<UCWidget_HUD, APlayerController>(GetController<APlayerController>(), HUDClass);
		HUD->AddToViewport();
		HUD->SetVisibility(ESlateVisibility::Visible);
		/*HUD->UpdateHP(GetCurrHP(), GetMaxHP());
		HUD->UpdateMP(GetCurrMP(), GetMaxMP());*/
	}
	StateComponent->OnAerialConditionChanged.AddUObject(this, &ACPlayer::OnAerialConditionChanged);
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/* IsInAir ���� �� �ݸ��� ������ ���� */
void ACPlayer::OnAerialConditionChanged(bool IsInAir) const
{
	/* ���߿� �߸� �ݸ��� �������� Ragdoll�� �����Ͽ� �ٸ� Pawn���� �浹 ���� */
	if(IsInAir)
	{
		GetCapsuleComponent()->SetCollisionProfileName("Ragdoll");
	}
	else
	{
		GetCapsuleComponent()->SetCollisionProfileName("Pawn");
	}
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//�� ��ǲ : �̵�, ī�޶�
	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	
	//�̵� �Է� ����, ���� �� �� �޸���
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
	
	//����
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACPlayer::PressedJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACPlayer::ReleasedJump);
	
	//ȸ��
	PlayerInputComponent->BindAction("Evade", IE_Pressed, this, &ACPlayer::PressedEvade);
	
	//���� ��ü
	PlayerInputComponent->BindAction("Weapon1", IE_Pressed, this, &ACPlayer::ChangeWeapon1);
	PlayerInputComponent->BindAction("Weapon2", IE_Pressed, this, &ACPlayer::ChangeWeapon2);
	PlayerInputComponent->BindAction("Weapon3", IE_Pressed, this, &ACPlayer::ChangeWeapon3);
	PlayerInputComponent->BindAction("Weapon4", IE_Pressed, this, &ACPlayer::ChangeWeapon4);

	//�׼� Ű
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &ACPlayer::PressedAction);
	PlayerInputComponent->BindAction("Action", IE_Released, this, &ACPlayer::ReleasedAction);

	//����׼� Ű
	PlayerInputComponent->BindAction("SubAction", IE_Pressed, this, &ACPlayer::PressedSubAction);
	PlayerInputComponent->BindAction("SubAction", IE_Released, this, &ACPlayer::ReleasedSubAction);
}

//////////////////////////////////////
///Axis Key Input
////////////////////////////////////////

void ACPlayer::OnMoveForward(float AxisValue)
{
	if(!StatusComponent->CanMove())
	{
		return;
	}
	const FRotator Rotator = FRotator(0, GetControlRotation().Yaw, 0);
	const FVector Direction = FQuat(Rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(Direction, AxisValue);
}

void ACPlayer::OnMoveRight(float AxisValue)
{
	if(!StatusComponent->CanMove())
	{
		return;
	}
	const FRotator Rotator = FRotator(0, GetControlRotation().Yaw, 0);
	const FVector Direction = FQuat(Rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(Direction, AxisValue);
}

void ACPlayer::OnVerticalLook(float AxisValue)
{
	if(!StatusComponent->GetFixedCamera())
	{
		AddControllerPitchInput(AxisValue);
	}
}

void ACPlayer::OnHorizontalLook(float AxisValue)
{
	if(!StatusComponent->GetFixedCamera())
	{
		AddControllerYawInput(AxisValue);
	}
}


////////////////////////////////////////
///Move Key Pressed
////////////////////////////////////////

void ACPlayer::PressedMoveF()
{
	if(StatusComponent->CanMove())
	{
		bMoving[0] = true;
	}
}
void ACPlayer::PressedMoveB()
{
	if(StatusComponent->CanMove())
	{
		bMoving[1] = true;
	}
}
void ACPlayer::PressedMoveL()
{
	if(StatusComponent->CanMove())
	{
		bMoving[2] = true;
	}
}
void ACPlayer::PressedMoveR()
{
	if(StatusComponent->CanMove())
	{
		bMoving[3] = true;
	}
}


////////////////////////////////////////
///Move Key Release
///
///��� Move Ű�� �� ���¸� Dash ����
////////////////////////////////////////

void ACPlayer::ReleasedMoveF()
{
	if(!StatusComponent->CanMove())
	{
		return;
	}
	
	bMoving[0] = false;
	if (!IsMoving())
	{
		if(StateComponent->IsDashMode())
		{
			StateComponent->SetIdleMode();
		}
		GetCharacterMovement()->MaxWalkSpeed = StatusComponent->GetWalkSpeed();
	}
}
void ACPlayer::ReleasedMoveB()
{
	if(!StatusComponent->CanMove())
	{
		return;
	}
	bMoving[1] = false;
	if (!IsMoving())
	{
		if(StateComponent->IsDashMode())
		{
			StateComponent->SetIdleMode();
		}
		GetCharacterMovement()->MaxWalkSpeed = StatusComponent->GetWalkSpeed();
	}
}
void ACPlayer::ReleasedMoveL()
{
	if(!StatusComponent->CanMove())
	{
		return;
	}
	bMoving[2] = false;
	if (!IsMoving())
	{
		if(StateComponent->IsDashMode())
		{
			StateComponent->SetIdleMode();
		}
		GetCharacterMovement()->MaxWalkSpeed = StatusComponent->GetWalkSpeed();
	}
}
void ACPlayer::ReleasedMoveR()
{
	if(!StatusComponent->CanMove())
	{
		return;
	}
	bMoving[3] = false;
	if (!IsMoving())
	{
		if(StateComponent->IsDashMode())
		{
			StateComponent->SetIdleMode();
		}
		GetCharacterMovement()->MaxWalkSpeed = StatusComponent->GetWalkSpeed();
	}
}

/* Dash, ���� �� �� ���� */
void ACPlayer::BeginRunning()
{
	if(StatusComponent->CanMove() && StatusComponent->CanDash())
	{
		StateComponent->SetDashMode();
		GetCharacterMovement()->MaxWalkSpeed = StatusComponent->GetRunSpeed();
	}
}

////////////////////////////////////////
///Weapon Change Key
////////////////////////////////////////

void ACPlayer::ChangeWeapon1()
{
	WeaponComponent->ChangeWeapon(1);
}
void ACPlayer::ChangeWeapon2()
{
	WeaponComponent->ChangeWeapon(2);
}
void ACPlayer::ChangeWeapon3()
{
	WeaponComponent->ChangeWeapon(3);
}
void ACPlayer::ChangeWeapon4()
{
	WeaponComponent->ChangeWeapon(4);
}

////////////////////////////////////////
///Action Key
////////////////////////////////////////

void ACPlayer::PressedJump()
{
	if(StatusComponent->CanAction())
	{
		ActionComponent->KeyPressed(EActionType::Jump);
	}
}

void ACPlayer::ReleasedJump()
{
	ActionComponent->KeyReleased(EActionType::Jump);
}

void ACPlayer::PressedEvade()
{
	if(StatusComponent->CanAction())
	{
		ActionComponent->KeyPressed(EActionType::Evade);
	}
}

void ACPlayer::PressedAction()
{
	ActionComponent->KeyPressed(EActionType::Action);
}

void ACPlayer::ReleasedAction()
{
	ActionComponent->KeyReleased(EActionType::Action);
}

void ACPlayer::PressedSubAction()
{
	ActionComponent->KeyPressed(EActionType::SubAction);
}

void ACPlayer::ReleasedSubAction()
{
	ActionComponent->KeyReleased(EActionType::SubAction);
}
