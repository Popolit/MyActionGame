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
	//WSAD 축입력
	void OnMoveForward(float AxisValue);
	void OnMoveRight(float AxisValue);

	//마우스 축입력
	void OnVerticalLook(float AxisValue);
	void OnHorizontalLook(float AxisValue);

	//점프
	void PressedJump();
	void ReleasedJump();

	//회피
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

	//무기 교체
	void ChangeWeapon1();
	void ChangeWeapon2();
	void ChangeWeapon3();
	void ChangeWeapon4();

	//좌클릭
	void PressedAction();
	void ReleasedAction();

	//우클릭
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
	float TimerToRefillEvadeCount;	//마지막 회피 이후 회피 카운트를 채우는 타이머
	
	float AimYaw;
	float AimPitch;

	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "HUD")
		TSubclassOf<class UCWidget_HUD> HUDClass;
	
private:
	UCWidget_HUD* HUD;
};
