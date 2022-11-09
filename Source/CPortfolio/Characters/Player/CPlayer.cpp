#include "CPlayer.h"
#include "Global.h"

#include "Animation/CAnimInstance.h"
#include "Widgets/CWidget_HUD.h"
#include "Attributes/CAttributeSet.h"
#include "Components/CWeaponComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"


//  *********************
//      �⺻ ����
//  *********************
ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;


	//�޽� ����
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Characters/Player/Meshes/SK_CyberpunkSamurai_WithHelmet.SK_CyberpunkSamurai_WithHelmet'");
	GetMesh()->SetSkeletalMesh(mesh);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	//ī�޶� ����
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	SpringArm->SetRelativeLocation(FVector(0, 0, 150));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bDoCollisionTest = false;

	Camera->SetRelativeLocation(FVector(-30, 0, 0));
	Camera->bUsePawnControlRotation = false;

	//�ִϸ��̼� ����
	TSubclassOf<UCAnimInstance> animInstance;
	CHelpers::GetClass<UCAnimInstance>(&animInstance, "AnimBlueprint'/Game/Animations/ABP_Character.ABP_Character_C'");
	GetMesh()->SetAnimClass(animInstance);
	
	UAnimMontage* jumpAnimMontage_1, *jumpAnimMontage_2;
	CHelpers::GetAsset<UAnimMontage>(&jumpAnimMontage_1, "AnimMontage'/Game/Montages/Player/Common/Jump_Start_Montage.Jump_Start_Montage'");
	CHelpers::GetAsset<UAnimMontage>(&jumpAnimMontage_2, "AnimMontage'/Game/Montages/Player/Common/DoubleJump_Montage.DoubleJump_Montage'");
	CHelpers::GetAsset<UAnimMontage>(&EvadeAnimMontage, "AnimMontage'/Game/Montages/Player/Common/Evade_Step_F_Montage.Evade_Step_F_Montage'");
	JumpAnimMontages.Add(jumpAnimMontage_1);
	JumpAnimMontages.Add(jumpAnimMontage_2);



	//HP, MP HUD Ŭ���� ����
	/* MaxHP = 10000.0f;
	CurrHP = MaxHP;
	MaxMP = 100.0f;
	CurrMP = 0.0f; */
	CHelpers::GetClass<UCWidget_HUD>(&HUDClass, "WidgetBlueprint'/Game/Widgets/WB_HUD.WB_HUD_C'");
	
	//Weapon ����
	CHelpers::CreateActorComponent<UCWeaponComponent>(this, &WeaponComponent, "Weapon");


	//ĳ���� �⺻ ����
	GetCharacterMovement()->MaxWalkSpeed = 400;
	GetCharacterMovement()->MaxAcceleration = 512;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	bCanEvade = true;

	JumpMaxCount = 2;
	JumpMaxHoldTime = 0.5f;
	MaxEvadeCount = 2;
	EvadeCount = MaxEvadeCount;
	Timer_RefillEvadeCount = 0.0f;

	for(UINT u = 0; u < 4; u++)
		bMoving[u] = false;
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
		HUD->UpdateHP(GetCurrHP(), GetMaxHP());
		HUD->UpdateMP(GetCurrMP(), GetMaxMP());
	}
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//������ ������ �ڿ� ����
	/* CurrMP += TickMPAmount; */
	//HUD->UpdateMP(GetCurrMP(), GetMaxMP());

	//ȸ�� Ƚ�� ����
	if (bCanEvade)
	{
		if (0 < Timer_RefillEvadeCount)
			Timer_RefillEvadeCount -= DeltaTime;
		else
			EvadeCount = MaxEvadeCount;
	}
}


//  *********************
//      Attribute ó��
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

	//�� ��ǲ : �̵�, ī�޶�
	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	
	//�̵� �Է� ����, ���� �� �� �޸���
	PlayerInputComponent->BindAction("MoveF", IE_Pressed, this, &ACPlayer::BeginMoveF);
	PlayerInputComponent->BindAction("MoveR", IE_Pressed, this, &ACPlayer::BeginMoveB);
	PlayerInputComponent->BindAction("MoveB", IE_Pressed, this, &ACPlayer::BeginMoveL);
	PlayerInputComponent->BindAction("MoveL", IE_Pressed, this, &ACPlayer::BeginMoveR);

	PlayerInputComponent->BindAction("MoveF", IE_Released, this, &ACPlayer::EndMoveF);
	PlayerInputComponent->BindAction("MoveR", IE_Released, this, &ACPlayer::EndMoveB);
	PlayerInputComponent->BindAction("MoveB", IE_Released, this, &ACPlayer::EndMoveL);
	PlayerInputComponent->BindAction("MoveL", IE_Released, this, &ACPlayer::EndMoveR);

	PlayerInputComponent->BindAction("MoveF", IE_DoubleClick, this, &ACPlayer::BeginRunning);
	PlayerInputComponent->BindAction("MoveR", IE_DoubleClick, this, &ACPlayer::BeginRunning);
	PlayerInputComponent->BindAction("MoveB", IE_DoubleClick, this, &ACPlayer::BeginRunning);
	PlayerInputComponent->BindAction("MoveL", IE_DoubleClick, this, &ACPlayer::BeginRunning);
	
	//����
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACPlayer::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACPlayer::StopJumping);
	
	//ȸ��
	PlayerInputComponent->BindAction("Evade", IE_Pressed, this, &ACPlayer::BeginEvade);
	
	//���� ��ü
	PlayerInputComponent->BindAction("Weapon1", IE_Pressed, this, &ACPlayer::OnEquip1);
	PlayerInputComponent->BindAction("Weapon2", IE_Pressed, this, &ACPlayer::OnEquip2);
	PlayerInputComponent->BindAction("Weapon3", IE_Pressed, this, &ACPlayer::OnEquip3);
	PlayerInputComponent->BindAction("Weapon4", IE_Pressed, this, &ACPlayer::OnEquip4);
}

void ACPlayer::BeginEvade()
{
	Super::BeginEvade();
	if (EvadeCount == 0)
		return;
	if (!bCanEvade || IsInAir)
		return;
	GetMesh()->GetAnimInstance()->Montage_Play(EvadeAnimMontage);
	bCanEvade = false;
	EvadeCount--;
}



void ACPlayer::EndEvade()
{
	Super::EndEvade();
	bCanEvade = true;
	Timer_RefillEvadeCount = 1.0f;
}

bool ACPlayer::IsMoving()
{
	return bMoving[0] || bMoving[1] || bMoving[2] || bMoving[3];
}


void ACPlayer::OnMoveForward(float AxisValue)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, AxisValue);
}

void ACPlayer::OnMoveRight(float AxisValue)
{
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

void ACPlayer::Jump()
{
	Super::Jump();
	//���� ī��Ʈ ��� �Ҹ�
	if (JumpCurrentCount == 2)
		return;

	//1�� ����
	if (JumpCurrentCount == 0 && !IsInAir)
	{
		GetMesh()->GetAnimInstance()->Montage_Play(JumpAnimMontages[0]);
		return;
	}
	//2�� ����
	if(JumpCurrentCount == 1 || IsInAir)
		GetMesh()->GetAnimInstance()->Montage_Play(JumpAnimMontages[1]);
}


void ACPlayer::BeginMoveF()
{
	bMoving[0] = true;
}
void ACPlayer::BeginMoveB()
{
	bMoving[1] = true;
}
void ACPlayer::BeginMoveL()
{
	bMoving[2] = true;
}
void ACPlayer::BeginMoveR()
{
	bMoving[3] = true;
}

void ACPlayer::EndMoveF()
{
	bMoving[0] = false;
	if(!IsMoving())
		GetCharacterMovement()->MaxWalkSpeed = 400;
}
void ACPlayer::EndMoveB()
{
	bMoving[1] = false;
	if (!IsMoving())
		GetCharacterMovement()->MaxWalkSpeed = 400;
}
void ACPlayer::EndMoveL()
{
	bMoving[2] = false;
	if (!IsMoving())
		GetCharacterMovement()->MaxWalkSpeed = 400;
}
void ACPlayer::EndMoveR()
{
	bMoving[3] = false;
	if (!IsMoving())
		GetCharacterMovement()->MaxWalkSpeed = 400;
}

void ACPlayer::BeginRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 800;
}


//  *********************
//      ���� ��ü
//  *********************
void ACPlayer::OnEquip1()
{
	Equip(0);
}
void ACPlayer::OnEquip2()
{
	Equip(1);
}
void ACPlayer::OnEquip3()
{
	Equip(2);
}
void ACPlayer::OnEquip4()
{
	Equip(3);
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
//      Equip ó��
//  *********************
void ACPlayer::Equip(uint8 const& InNumber)
{
	Super::Equip(InNumber);
	CheckNull(WeaponComponent);
	WeaponComponent->Equip(InNumber);
}

void ACPlayer::UnEquip()
{
	Super::UnEquip();
	CheckNull(WeaponComponent);
	WeaponComponent->UnEquip();
}
