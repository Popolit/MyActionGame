#include "Characters/CCharacter_Base.h"
#include "Global.h"

#include "Attributes/CAttributeSet.h"
#include "Components/CAbilitySystemComponent.h"
#include "Actions/CActionStructure.h"
#include "Actions/CAction.h"
#include "Actions/CI_Action_Tick.h"
#include "Components/CActionComponent.h"
#include "Components/CWeaponComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CFeetComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"


//  *********************
//      기본 세팅
//  *********************
ACCharacter_Base::ACCharacter_Base()
{
	CHelpers::CreateActorComponent<UCAbilitySystemComponent>(this, &AbilitySystemComponent, "AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	CHelpers::CreateActorComponent<UCAttributeSet>(this, &AttributeSet, "AttributeSet");
	bAbilitiesInitialized = false;

	//Weapon 설정
	CHelpers::CreateActorComponent<UCWeaponComponent>(this, &WeaponComponent, "Weapon");
	CHelpers::CreateActorComponent<UCActionComponent>(this, &ActionComponent, "Action");
	CHelpers::CreateActorComponent<UCStatusComponent>(this, &StatusComponent, "Status");
	CHelpers::CreateActorComponent<UCStateComponent>(this, &StateComponent, "State");
	CHelpers::CreateActorComponent<UCFeetComponent>(this, &FeetComponent, "Feet");
}

void ACCharacter_Base::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// Initialize
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AddStartupGameplayAbilities();
	}
}
void ACCharacter_Base::UnPossessed()
{
	
}


void ACCharacter_Base::OnRep_Controller()
{
	Super::OnRep_Controller();

	if (AbilitySystemComponent)
		AbilitySystemComponent->RefreshAbilityActorInfo();
}

void ACCharacter_Base::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

//  *********************
//      Movement 처리
//  *********************

void ACCharacter_Base::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PrevCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PrevCustomMode);
	EMovementMode NewMovementMode = GetCharacterMovement()->MovementMode;
	if(NewMovementMode == EMovementMode::MOVE_Flying)
		StateComponent->SetIsInAir(true);
			
}

void ACCharacter_Base::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();
	StateComponent->SetIsInAir(true);
	if(OnJumped.IsBound())
		OnJumped.Broadcast();
}

void ACCharacter_Base::OnWalkingOffLedge_Implementation(const FVector& PreviousFloorImpactNormal, const FVector& PreviousFloorContactNormal, const FVector& PreviousLocation, float TimeDelta)
{
	Super::OnWalkingOffLedge_Implementation(PreviousFloorImpactNormal, PreviousFloorContactNormal, PreviousLocation, TimeDelta);

	StateComponent->SetIsInAir(true);
}

void ACCharacter_Base::LaunchCharacter(FVector LaunchVelocity, bool bXYOverride, bool bZOverride)
{
	Super::LaunchCharacter(LaunchVelocity, bXYOverride, bZOverride);
	if(!bZOverride)
		return;
	StateComponent->SetIsInAir(true);
}

void ACCharacter_Base::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	StateComponent->SetIsInAir(false);
}

//  *********************
//		Attribute 처리
//  *********************
float ACCharacter_Base::GetCurrHP() const
{
	if(!!AttributeSet)
		return AttributeSet->GetCurrHP();
	return 1.0f;
}

float ACCharacter_Base::GetMaxHP() const
{
	if(!!AttributeSet)
		return AttributeSet->GetMaxHP();
	return 0.0f;
}

float ACCharacter_Base::GetMoveSpeed() const
{
	if(!!AttributeSet)
		return AttributeSet->GetMoveSpeed();
	return 0.0f;
}

void ACCharacter_Base::HandleDamage(float InAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ACCharacter_Base* InstigatorCharacter, AActor* DamageCauser)
{
	OnDamaged(InAmount, HitInfo, DamageTags, InstigatorCharacter, DamageCauser);	
}

void ACCharacter_Base::HandleHPChanged(float InAmount, const struct FGameplayTagContainer& EventTags)
{
	if (bAbilitiesInitialized)
		OnHPChanged(InAmount, EventTags);
}

void ACCharacter_Base::HandleMPChanged(float InAmount, const struct FGameplayTagContainer& EventTags)
{
	if (bAbilitiesInitialized)
		OnMPChanged(InAmount, EventTags);
}

void ACCharacter_Base::HandleMoveSpeedChanged(float InAmount, const struct FGameplayTagContainer& EventTags)
{
	GetCharacterMovement()->MaxWalkSpeed = GetMoveSpeed();
	if (bAbilitiesInitialized)
		OnMoveSpeedChanged(InAmount, EventTags);
}


//  *********************
//      Ability 처리
//  *********************

void ACCharacter_Base::GetActiveAbilitiesWithTags(FGameplayTagContainer AbilityTags, TArray<UCGameplayAbility*>& ActiveAbilities)
{
	CheckNull(AbilitySystemComponent);
	AbilitySystemComponent->GetActiveAbilitiesWithTags(AbilityTags, ActiveAbilities);
}

UAbilitySystemComponent* ACCharacter_Base::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void ACCharacter_Base::AddStartupGameplayAbilities()
{
	CheckNull(AbilitySystemComponent);
	if(bAbilitiesInitialized)
		return;
	if (GetLocalRole() != ROLE_Authority)
		return;

	for (TSubclassOf<UCGameplayAbility>& StartupAbility : GameplayAbilities)
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility, 1, INDEX_NONE, this));

	 // Now apply passives
	for (TSubclassOf<UGameplayEffect>& GameplayEffect : StartupEffects)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
		}
	} 

	bAbilitiesInitialized = true;
}


void ACCharacter_Base::RemoveStartupGameplayAbilities()
{
	CheckNull(AbilitySystemComponent);
	if(GetLocalRole() != ROLE_Authority)
		return;
	if(!bAbilitiesInitialized)
		return;

	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
	for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if ((Spec.SourceObject == this) && GameplayAbilities.Contains(Spec.Ability->GetClass()))
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}

	for (int32 i = 0; i < AbilitiesToRemove.Num(); i++)
		AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);

	FGameplayEffectQuery Query;
	Query.EffectSource = this;
	AbilitySystemComponent->RemoveActiveEffects(Query);

	//RemoveSlottedGameplayAbilities(true);

	bAbilitiesInitialized = false;
}

//  *********************
//      Equip 처리
//  *********************
void ACCharacter_Base::ChangeWeapon(uint8 const& InNumber) {}



//  *********************
//      데미지 처리
//  *********************

float ACCharacter_Base::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if(DamageAmount == 0.f)
		return 0.f;
	if(!DamageEvent.IsOfType(FActionDamageEvent::ClassID))
		return 0.f;
	
	FActionDamageEvent* const actionDamageEvent = (FActionDamageEvent*) &DamageEvent;

	//데미지 방향 벡터 설정
	FVector damageDirection;

	//직접 타격
	if(EventInstigator)
		damageDirection = GetActorLocation() - EventInstigator->GetPawn()->GetActorLocation();
	//스킬 등 투사체 타격
	else
		damageDirection = GetActorLocation() - DamageCauser->GetActorLocation();
	damageDirection.Z = 0.f;
	damageDirection.Normalize();
	
	//넉백 벡터 설정
	FVector knockBack = damageDirection;
	knockBack *= actionDamageEvent->HitData->Launch;
	knockBack.Z += actionDamageEvent->HitData->LaunchZ;

	if(StateComponent->IsInAir())
		LaunchCharacter(knockBack.Z == 0.f ? LaunchZ_InAir : knockBack, true, true);
	else if(knockBack.Z == 0.f)
		LaunchCharacter(knockBack, true, false);
	else
		LaunchCharacter(knockBack, true, true);
	
	//캐릭터 방향 세팅
	SetActorRotation(UKismetMathLibrary::MakeRotFromX(-damageDirection));


	//피격 처리
	
	actionDamageEvent->HitData->PlayHitStop(GetWorld());
	actionDamageEvent->HitData->PlayEffect(GetWorld(), GetActorLocation());
	actionDamageEvent->HitData->PlaySoundCue(this);
	
	StatusComponent->Damage(DamageAmount);
	StateComponent->SetHittedMode();
	
	UCAction* action = ActionComponent->GetAction(EActionType::None);
	ICI_Action_Tick* tickableAction = Cast<ICI_Action_Tick>(action);

	if(tickableAction)
		tickableAction->SetTickTime(actionDamageEvent->HitData->StaggerTime);

	return DamageAmount;
}


//  *********************
//      사망 처리
//  *********************
void ACCharacter_Base::CharacterDie()
{
	//RemoveCharacterAbilities();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale = 0.0f;
	GetCharacterMovement()->Velocity = FVector(0);

	OnCharacterDied.Broadcast(this);

	if(!!AbilitySystemComponent)
		AbilitySystemComponent->CancelAbilities();
	if(!!DeathMontage)
		PlayAnimMontage(DeathMontage);
	else
		EndDying();
}

void ACCharacter_Base::EndDying()
{
	Destroy();
}





