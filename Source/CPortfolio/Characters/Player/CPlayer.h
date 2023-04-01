#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Characters/CCharacter_Base.h"

#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class CPORTFOLIO_API ACPlayer : public ACCharacter_Base
{
	GENERATED_BODY()
public:
	ACPlayer();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnAerialConditionChanged(bool IsInAir);

public:
	FORCEINLINE FRotator GetCameraRotation() const { return Camera->GetComponentRotation(); }
	FORCEINLINE float GetAimPitch() const { return AimPitch; }
	FORCEINLINE float GetAimYaw() const { return AimYaw; }
	FORCEINLINE bool IsMoving() const { return bMoving[0] || bMoving[1] || bMoving[2] || bMoving[3]; }

private:
	//WSAD ���Է�
	void OnMoveForward(float AxisValue);
	void OnMoveRight(float AxisValue);

	//���콺 ���Է�
	void OnVerticalLook(float AxisValue);
	void OnHorizontalLook(float AxisValue);

	//����
	void PressedJump();
	void ReleasedJump();

	//ȸ��
	void PressedEvade();
	
	//WSAD
	void PressedMoveF();
	void PressedMoveB();
	void PressedMoveL();
	void PressedMoveR();

	//WSAD Release
	void ReleasedMoveF();
	void ReleasedMoveB();
	void ReleasedMoveL();
	void ReleasedMoveR();

	void BeginRunning();

	//���� ��ü
	void ChangeWeapon1();
	void ChangeWeapon2();
	void ChangeWeapon3();
	void ChangeWeapon4();

	//��Ŭ��
	void PressedAction();
	void ReleasedAction();

	//��Ŭ��
	void PressedSubAction();
	void ReleasedSubAction();

private:
	UPROPERTY(VisibleDefaultsOnly)
		USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleDefaultsOnly)
		UCameraComponent* Camera;
	
private:
	bool bMoving[4];	//{Forward, Backward, Left, Right}
	
	int MaxEvadeCount;
	int EvadeCount;
	float TimerToRefillEvadeCount;	//������ ȸ�� ���� ȸ�� ī��Ʈ�� ä��� Ÿ�̸�
	
	float AimYaw;
	float AimPitch;

	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "HUD")
		TSubclassOf<class UCWidget_HUD> HUDClass;
	
private:
	UCWidget_HUD* HUD;
};
