#pragma once

#include "CoreMinimal.h"
#include "Characters/CCharacter_Base.h"

#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

UCLASS()
class CPORTFOLIO_API ACPlayer : public ACCharacter_Base
{
	GENERATED_BODY()


//  *********************
//      기본 세팅
//  *********************
public:

	ACPlayer();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;


//  *********************
//      Attribute 처리
//  *********************
public:
	UFUNCTION(BlueprintCallable, Category = "Attribute")
		float GetCurrMP() const;
	UFUNCTION(BlueprintCallable, Category = "Attribute")
		float GetMaxMP() const;

/* protected:
	void HandleDamage(float InAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ACCharacter_Base* InstigatorCharacter, AActor* DamageCauser);
	void HandleHPChanged(float InAmount, const struct FGameplayTagContainer& EventTags);
	void HandleMPChanged(float InAmount, const struct FGameplayTagContainer& EventTags);
	void HandleMoveSpeedChanged(float InAmount, const struct FGameplayTagContainer& EventTags);

 */

//  *********************
//      입력 처리
//  *********************
public:
	FORCEINLINE float GetAimPitch() const { return AimPitch; }
	FORCEINLINE float GetAimYaw() const { return AimYaw; }

public:
	virtual void BeginEvade() override;
	virtual void EndEvade() override;
	bool IsMoving();
private:
	//WSAD 축입력
	void OnMoveForward(float AxisValue);
	void OnMoveRight(float AxisValue);

	//마우스 축입력
	void OnVerticalLook(float AxisValue);
	void OnHorizontalLook(float AxisValue);

	void Jump() override;
	
	//WSAD
	void BeginMoveF();
	void BeginMoveB();
	void BeginMoveL();
	void BeginMoveR();

	//WSAD Release
	void EndMoveF();
	void EndMoveB();
	void EndMoveL();
	void EndMoveR();

	void BeginRunning();

	//무기 교체
	void OnEquip1();
	void OnEquip2();
	void OnEquip3();
	void OnEquip4();

public:
	void UseControlRotation();
	void NotUseControlRotation();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

//  *********************
//      Equip 처리
//  *********************
private:
	virtual void Equip(uint8 const& InNumber = 0) override;
	virtual void UnEquip() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "HUD")
		TSubclassOf<class UCWidget_HUD> HUDClass;
private:
	class UCWidget_HUD* HUD;

	UPROPERTY(VisibleDefaultsOnly)
		class UCWeaponComponent* WeaponComponent;

private:
	bool bMoving[4];	//{Forward, Backward, Left, Right}
	bool bCanEvade;

private:
	TArray<class UAnimMontage*> JumpAnimMontages;
	class UAnimMontage* EvadeAnimMontage;
	int MaxEvadeCount;
	int EvadeCount;
	float Timer_RefillEvadeCount;	//마지막 회피 이후 회피 카운트를 채우는 타이머
	
	
	float AimYaw;
	float AimPitch;
};
