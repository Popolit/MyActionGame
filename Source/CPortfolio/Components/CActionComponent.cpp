#include "CActionComponent.h"
#include "CHelpers.h"

#include "Actions/BaseClasses/CAction_Base.h"
#include "ActionSet.h"
#include "Weapon.h"
#include "CWeaponComponent.h"
#include "WeaponAttachment.h"
#include "Characters/CCharacter_Base.h"

#include "IKeyInput.h"
#include "Interfaces/CI_Collision.h"
#include "Interfaces/CI_EventHandler.h"
#include "Interfaces/CI_ToggleEventHandler.h"


UCActionComponent::UCActionComponent() : ActionSet(nullptr)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();

	//오너 캐릭터 세팅
	OwnerCharacter = Cast<ACCharacter_Base>(GetOwner());
	check(OwnerCharacter);

	UCWeaponComponent* WeaponComponent = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter);

	//WeaponComponent를 먼저 BeginPlay()
	if(!WeaponComponent->HasBegunPlay())
	{
		WeaponComponent->BeginPlay();
	}

	//델리게이션 세팅 및 ActionSet 가져오기
	WeaponComponent->OnWeaponChanged.AddUObject(this, &UCActionComponent::OnWeaponChanged);
	ActionSet = WeaponComponent->GetWeapon()->GetActionSet();

	//Attachment의 델리게이션 세팅
	for(AWeaponAttachment* Attachment : WeaponComponent->GetWeapon()->GetAttachments())
	{
		Attachment->OnWeaponAttachmentBeginOverlap.BindUObject(this, &UCActionComponent::OnAttachmentBeginOverlap);
		Attachment->OnWeaponAttachmentOffCollision.BindUObject(this, &UCActionComponent::OnAttachmentOffCollision);
	}

	if(ActionSet != nullptr)
	{
		ActionSet->SetAllDelegations<UCActionComponent>(this, &UCActionComponent::OnActionBegin);
	}
}

/* ActionEvent 등록 */
void UCActionComponent::BindActionEvent(FName const& InEventName, ICI_EventHandler* InEventHandler)
{
	ActionEvents.Add(InEventName, Cast<UCAction_Base>(InEventHandler));
}

/* ActionToggleEvent 등록 */
void UCActionComponent::BindActionEvent(FName const& InEventName, ICI_ToggleEventHandler* InEventHandler)
{
	ActionToggleEvents.Add(InEventName, Cast<UCAction_Base>(InEventHandler));
}

/* Weapon이 변경되면 실행되는 함수 */
void UCActionComponent::OnWeaponChanged(UWeapon* PrevWeapon, UWeapon* NewWeapon)
{
	//이전 콜리전 델리게이션 해제
	if(PrevWeapon != nullptr)
	{
		for(AWeaponAttachment* Attachment : PrevWeapon->GetAttachments())
		{
			Attachment->OnWeaponAttachmentBeginOverlap.Unbind();
			Attachment->OnWeaponAttachmentOffCollision.Unbind();
		}
	}

	if(NewWeapon == nullptr)
	{
		return;
	}

	//새 콜리전 델리게이션 등록
	for(AWeaponAttachment* Attachment : NewWeapon->GetAttachments())
	{
		Attachment->OnWeaponAttachmentBeginOverlap.BindUObject(this, &UCActionComponent::OnAttachmentBeginOverlap);
		Attachment->OnWeaponAttachmentOffCollision.BindUObject(this, &UCActionComponent::OnAttachmentOffCollision);
	}

	//최근 액션 종료
	if(CurrAction != nullptr && !CurrAction->IsActionEnded())
	{
		CurrAction->EndAction();
	}

	//액션 셋 세팅
	ActionSet->UnsetAllDelegations();
	ActionSet = NewWeapon->GetActionSet();

	//새로 델리게이션 세팅
	if(ActionSet != nullptr)
	{
		ActionSet->SetAllDelegations<UCActionComponent>(this, &UCActionComponent::OnActionBegin);
	}
}

//새 액션이 시작 시, 이전 액션 종료
void UCActionComponent::OnActionBegin(UAction* InAction)
{
	if(CurrAction != nullptr && CurrAction != InAction && !CurrAction->IsActionEnded())
	{
		CurrAction->EndAction();
	}
	CurrAction = InAction;
}

/**
 * 액션 이벤트 발생
 * @param InEventName 이벤트 이름
 */
void UCActionComponent::OnActionEvent(FName const& InEventName)
{
	if(ActionEvents.Contains(InEventName))
	{
		ICI_EventHandler* EventHandler = Cast<ICI_EventHandler>(ActionEvents[InEventName]);
		if(EventHandler != nullptr)
		{
			EventHandler->HandleEvent();
		}
	}
}

void UCActionComponent::OnActionEvent(FName const& InEventName, bool const& IsEventOn)
{
	if(ActionToggleEvents.Contains(InEventName))
	{
		ICI_ToggleEventHandler* EventHandler = Cast<ICI_ToggleEventHandler>(ActionToggleEvents[InEventName]);
		if(EventHandler != nullptr)
		{
			EventHandler->HandleEvent(IsEventOn);
		}
	}
}

void UCActionComponent::OnAttachmentBeginOverlap(AActor* InAttackCauser, AActor* InTargetActor)
{
	ICI_Collision* Action_HasCollision = Cast<ICI_Collision>(CurrAction);
	if(Action_HasCollision == nullptr)
	{
		return;
	}

	//이미 충돌한 액터라면 무시
	if(HitActors.Contains(InTargetActor))
	{
		return;
	}
	
	Action_HasCollision->OnCollision(InAttackCauser, InTargetActor);
	HitActors.Push(InTargetActor);
}



void UCActionComponent::OnAttachmentOffCollision()
{
	HitActors.Empty();
}

void UCActionComponent::KeyPressed(EActionType const& InActionInput) const
{
	if(ActionSet == nullptr)
	{
		return;
	}
	
	//Air Action
	if(OwnerCharacter->IsInAir())
	{
		UAction* Action = ActionSet->GetActionsInAir()[(uint8)InActionInput];
		IIKeyInput* KeyInputAction = Cast<IIKeyInput>(Action);
		if(KeyInputAction != nullptr)
		{
			KeyInputAction->KeyPressed();
		}
	}
	//Ground Action
	else
	{
		UAction* Action = ActionSet->GetActions()[(uint8)InActionInput];
		IIKeyInput* KeyInputAction = Cast<IIKeyInput>(Action);
		if(KeyInputAction != nullptr)
		{
			KeyInputAction->KeyPressed();
		}
	}
}

void UCActionComponent::KeyReleased(EActionType const& InActionInput) const
{
	if(ActionSet == nullptr)
	{
		return;
	}
	UAction* Action = ActionSet->GetActions()[(uint8)InActionInput];
	IIKeyInput* KeyInputAction = Cast<IIKeyInput>(Action);
	if(KeyInputAction != nullptr)
	{
		KeyInputAction->KeyReleased();
	}
}



