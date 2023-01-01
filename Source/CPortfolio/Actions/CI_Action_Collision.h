#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CI_Action_Collision.generated.h"

class UCAction;
UINTERFACE()
class UCI_Action_Collision : public UInterface
{
	GENERATED_BODY()
};

class ICI_Action_Collision
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void OnAttachmentBeginOverlap(class ACCharacter_Base* InAttacker, AActor* InAttackCauser, ACCharacter_Base* InOtherCharacter);
	void OnAttachmentBeginOverlap_Implemantation(class ACCharacter_Base* InAttacker, AActor* InAttackCauser, ACCharacter_Base* InOtherCharacter);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void OnAttachmentEndOverlap(ACCharacter_Base* InAttacker, AActor* InAttackCauser, ACCharacter_Base* InOtherCharacter);
	void OnAttachmentEndOverlap_Implemantation(class ACCharacter_Base* InAttacker, AActor* InAttackCauser, ACCharacter_Base* InOtherCharacter);
};
