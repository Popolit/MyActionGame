#include "ActionFunctions.h"
#include "CHelpers.h"

#include "Components/CStatusComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/Character.h"

/**
 * Do Action - 애님 몽타주의 재생과 해당 액션 동안 상태 변화를 처리
 * @param InActionData ActionData Input
 * @param InOwnerCharacter 대상 캐릭터
 */
void ActionFunctions::DoAction(FActionData const& InActionData, ACharacter* InOwnerCharacter)
{
	if(InActionData.Montage == nullptr)
	{
		return;
	}

	InOwnerCharacter->PlayAnimMontage(InActionData.Montage, InActionData.PlayRatio);
	UCStatusComponent* StatusComponent = CHelpers::GetComponent<UCStatusComponent>(InOwnerCharacter);

	if (StatusComponent == nullptr)
	{
		return;
	}
	
	if(!InActionData.bCanMove)
	{
		StatusComponent->DisableMove();
	}
	if (InActionData.bFixedCamera)
	{
		StatusComponent->EnableFixedCamera();
	}
}

/**
 * End Action - 액션을 마무리하고 오너 캐릭터의 상태를 되돌림
 * @param InOwnerCharacter 대상 캐릭터
 */
void ActionFunctions::EndAction(ACharacter* InOwnerCharacter)
{
	UCStatusComponent* StatusComponent = CHelpers::GetComponent<UCStatusComponent>(InOwnerCharacter);
	if (StatusComponent != nullptr)
	{
		StatusComponent->EnableMove();
		StatusComponent->DisableFixedCamera();
	}
}

/**
 * Action으로 인해 Hit 발생 시 피격 효과를 재생
 * @param InHitData 히트 데이터
 * @param InAttacker 공격을 가한 캐릭터
 * @param InTargetActor 공격에 맞은 액터
 */
void ActionFunctions::PlayHitEffect(FHitData const& InHitData, ACharacter* InAttacker, AActor* InTargetActor)
{
	//Effect
	if(InHitData.Effect == nullptr)
	{
		return;
	}

	const UWorld* World = InTargetActor->GetWorld();
	const FVector ActorLocation = InTargetActor->GetActorLocation();
	const FVector EffectLocation = ActorLocation + InTargetActor->GetActorRotation().RotateVector(InHitData.EffectLocation);

	//히트 이펙트를 재생할 트랜스폼 설정
	FTransform Transform;
	Transform.SetLocation(EffectLocation);
	Transform.SetRotation(FQuat(InTargetActor->GetActorRotation()));
	Transform.SetScale3D(InHitData.EffectScale);

	UParticleSystem* Particle = Cast<UParticleSystem>(InHitData.Effect);
	UNiagaraSystem* Niagara = Cast<UNiagaraSystem>(InHitData.Effect);

	//이펙트가 파티클인 경우
	if (Particle != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(InTargetActor->GetWorld(), Particle, Transform);
	}

	//이펙트가 나이아가라인 경우
	if (Niagara != nullptr)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(InTargetActor->GetWorld(), Niagara, Transform.GetLocation(), FRotator(Transform.GetRotation()), Transform.GetScale3D());
	}

	// Sound
	if(InHitData.SoundCue != nullptr)
	{
		UGameplayStatics::SpawnSoundAtLocation(World, InHitData.SoundCue, ActorLocation);
	}

	//HitStop & 역경직
	const float OriginalTimeSpeed_Attacker = InAttacker->CustomTimeDilation;
	const float OriginalTimeSpeed_Target = InTargetActor->CustomTimeDilation;

	//공격자와 피격자는 각각 일정 시간동안 시간이 느려짐
	InAttacker->CustomTimeDilation = HitStopTimeSpeed;
	InTargetActor->CustomTimeDilation = HitStopTimeSpeed;

	//지정한 시간이 지나면 원래의 속도로 돌아옴
	const FTimerDelegate TimerDelegate = FTimerDelegate::CreateLambda([=]()
	{
		InAttacker->CustomTimeDilation = OriginalTimeSpeed_Attacker;
		InTargetActor->CustomTimeDilation = OriginalTimeSpeed_Target;
	});

	FTimerHandle TimerHandle;
	World->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, InHitData.StopTime, false);
}

/**
 * Action에 의해 Hit한 대상이 Damage를 입으면 해당 Damage를 처리함
 * @param InHitData 히트 데이터
 * @param InAttacker 공격을 가한 캐릭터
 * @param InAttackCauser 공격의 원인이 된 액터 (Weapon이나 스킬 액터 등)
 * @param InTargetActor 공격에 맞은 액터
 */
void ActionFunctions::SendDamage(FHitData* InHitData, ACharacter* InAttacker, AActor* InAttackCauser,
	AActor* InTargetActor)
{
	FActionDamageEvent DamageEvent;
	DamageEvent.HitData = InHitData;

	InTargetActor->TakeDamage(InHitData->Damage, DamageEvent, InAttacker->GetController(), InAttackCauser);
}
