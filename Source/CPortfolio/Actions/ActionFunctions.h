#pragma  once
#include "CoreMinimal.h"
#include "ActionStructure.h"

class ActionFunctions
{
public:
	static void DoAction(FActionData const& InActionData, ACharacter* InOwnerCharacter);
	static void EndAction(ACharacter* InOwnerCharacter);
	static void PlayHitEffect(FHitData const& InHitData, ACharacter* InAttacker, AActor* InTargetActor);
	static void SendDamage(FHitData* InHitData, ACharacter* InAttacker, AActor* InAttackCauser, AActor* InTargetActor);

private:
	static constexpr float HitStopTimeSpeed = 1e-3f;
};