#pragma  once
#include "CoreMinimal.h"
#include "ActionStructure.h"

class ActionFunctions
{
public:
	static void DoAction(FActionData const& InActionData, ACharacter* InOwnerCharacter);
	static void EndAction(ACharacter* InOwnerCharacter);
	static void PlayEffect(FActionData const& InActionData, ACharacter* InOwnerCharacter);
};