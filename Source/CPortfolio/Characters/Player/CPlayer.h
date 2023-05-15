#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Characters/CCharacter_Base.h"
#include "CPlayer.generated.h"

class USpringArmComponent;

/* Player Class */
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
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	void OnAerialConditionChanged(bool IsInAir) const;

public:
	virtual float GetAimPitch() const override;
	FORCEINLINE FRotator GetCameraRotation() const { return Camera->GetComponentRotation(); }
	FORCEINLINE bool IsMoving() const { return bMoving[0] || bMoving[1] || bMoving[2] || bMoving[3]; }

private:
	//WSAD ���Է�
	void OnMoveForward(float AxisValue);
	void OnMoveRight(float AxisValue);

	//���콺 ���Է�
	void OnVerticalLook(float AxisValue);
	void OnHorizontalLook(float AxisValue);
	
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

	//����
	void PressedJump();
	void ReleasedJump();

	//ȸ��
	void PressedEvade();
	
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


	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "HUD")
		TSubclassOf<class UCWidget_HUD> HUDClass;
	
private:
	UCWidget_HUD* HUD;
};
