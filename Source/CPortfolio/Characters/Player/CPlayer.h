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


		
protected:
	UPROPERTY(EditDefaultsOnly, Category = "HUD")
		TSubclassOf<class UCWidget_HUD> HUDClass;


//  *********************
//      Attribute 처리
//  *********************
public:
	UFUNCTION(BlueprintCallable, Category = "Attribute")
		float GetCurrMP() const;
	UFUNCTION(BlueprintCallable, Category = "Attribute")
		float GetMaxMP() const;

protected:
	UFUNCTION(BlueprintImplementableEvent)
		void OnMPChanged(float InAmount, const struct FGameplayTagContainer& EventTags);
protected:
	virtual void HandleMPChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
protected:
	void SetCurrMP(float InAmount);
	void SetMaxMP(float InAmount); 

	void HandleDamage(float InAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ACCharacter_Base* InstigatorCharacter, AActor* DamageCauser);
	void HandleHPChanged(float InAmount, const struct FGameplayTagContainer& EventTags);
	void HandleMPChanged(float InAmount, const struct FGameplayTagContainer& EventTags);
	void HandleMoveSpeedChanged(float InAmount, const struct FGameplayTagContainer& EventTags);



public:
	FORCEINLINE float GetAimPitch() { return AimPitch; }
	FORCEINLINE float GetAimYaw() { return AimYaw; }

public:
	void BeginEvade() override;
	void EndEvade() override;
	bool IsMoving();
private:
	void OnMoveForward(float AxisValue);
	void OnMoveRight(float AxisValue);
	void OnVerticalLook(float AxisValue);
	void OnHorizontalLook(float AxisValue);

	void Jump() override;
	

	void BeginMoveF();
	void BeginMoveB();
	void BeginMoveL();
	void BeginMoveR();

	void EndMoveF();
	void EndMoveB();
	void EndMoveL();
	void EndMoveR();

	void BeginRunning();

public:
	void UseControlRotation();
	void NotUseControlRotation();


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	class UCWidget_HUD* HUD;

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
