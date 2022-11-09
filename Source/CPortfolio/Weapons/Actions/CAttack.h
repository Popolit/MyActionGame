#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Weapons/CWeaponStructure.h"
#include "CAttack.generated.h"

UCLASS(Blueprintable)
class CPORTFOLIO_API UCAttack : public UObject
{
	GENERATED_BODY()
	
public:
	FORCEINLINE void SetEquipping(const bool* InEquipping) { bEquipping = InEquipping; }
	FORCEINLINE bool GetBeginAction() { return bBeginAction; }

public:
	UCAttack();

	virtual void BeginPlay(class ACAttachment* InAttachment, class ACharacter* InOwner, const TArray<FAttackData>& InAttackDatas, const TArray<FHitData>& InHitDatas);

public:
	virtual void Attack() { }
	virtual void Begin_Attack();
	virtual void End_Attack();

	virtual void Tick(float InDeltaTime) { }

public:
	UFUNCTION()
		virtual void OnEquip(){ }

	UFUNCTION()
		virtual void OnUnequip() { }

public:
	UFUNCTION()
		virtual void OnAttachmentCollision() { }

	UFUNCTION()
		virtual void OffAttachmentCollision() { }

	UFUNCTION()
		virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) { }

	UFUNCTION()
		virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) { }

protected:
	class ACharacter* OwnerCharacter;
	class UWorld* World;

	class UCStateComponent* State;
	
	TArray<FAttackData> AttackDatas;
	TArray<FHitData> HitDatas;

	const bool* bEquipping;
	bool bBeginAction;
};
