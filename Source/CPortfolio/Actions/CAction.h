#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CActionStructure.h"
#include "Components/CStatusComponent.h"
#include "CAction.generated.h"


UCLASS(Blueprintable)
class CPORTFOLIO_API UCAction : public UObject
{
	GENERATED_BODY()

public:
	UCAction();

	virtual void BeginPlay(class ACCharacter_Base* InOwner, const TArray<struct FActionMontage>& InActionMontages);
	
public:
	UFUNCTION(BlueprintNativeEvent)
		void Pressed();
	virtual void Pressed_Implementation();
	UFUNCTION(BlueprintNativeEvent)
		void Released();
	virtual void Released_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void DoAction(FActionMontage const& InActionMontage);
	virtual void DoAction_Implementation(FActionMontage const& InActionMontage);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void EndAction();
	virtual void EndAction_Implementation();

public:
	UFUNCTION(BlueprintCallable)
		void PlayEffect(FActionMontage const& InActionMontage);
	UFUNCTION(BlueprintCallable)
		void PlayEffectAtSocket(FActionMontage const& InActionMontage, USkeletalMeshComponent* InMesh, FName InSocketName);

public:
	UFUNCTION()
		virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) { }

	UFUNCTION()
		virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) { }

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACCharacter_Base* OwnerCharacter;
	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;
	UPROPERTY(BlueprintReadOnly)
		class UCStatusComponent* Status;
	UPROPERTY(BlueprintReadOnly)
		TArray<struct FActionMontage> ActionMontages;


public:
	FORCEINLINE bool CanAction() { return Status->CanAction(); }
	
protected:
	bool bInterrupted;
};


