#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CSubAction.generated.h"

UCLASS(Blueprintable)
class CPORTFOLIO_API UCSubAction : public UObject
{
	GENERATED_BODY()
	
public:
	UCSubAction();

public:
	virtual void BeginPlay(class ACharacter* InOwner, class ACAttachment* InAttachment, class UCAttack* InAttack);

public:
	virtual void Pressed() {}
	virtual void Released() {}

	UFUNCTION(BlueprintNativeEvent)
		void Begin_SubAction();
		virtual void Begin_SubAction_Implementation() {}

	UFUNCTION(BlueprintNativeEvent)
		void End_SubAction();
		virtual void End_SubAction_Implementation() {}

	UFUNCTION(BlueprintNativeEvent)
		void Tick(float DeltaTime);
		virtual void Tick_Implementation(float DeltaTime) {}

public:
	UFUNCTION()
		virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) {}
	
	UFUNCTION()
		virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) {}

	UFUNCTION()
		virtual void OnAttachmentCollision() {}

	UFUNCTION()
		virtual void OffAttachmentCollision() {}

protected:
	class ACharacter* OwnerCharacter;
	class UWorld* World;
	class UCStateComponent* State;
	class UCStatusComponent* Status;
};
