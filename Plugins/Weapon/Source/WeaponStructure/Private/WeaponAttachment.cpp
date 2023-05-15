#include "WeaponAttachment.h"

#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"

/* Collision 채널을 추가하도록 수정 필요 */
AWeaponAttachment::AWeaponAttachment() : HolsterSocketName("Root"), EquipSocketName("Root")
{
	Root = this->CreateDefaultSubobject<USceneComponent>("Root");
	this->SetRootComponent(Root);
}

void AWeaponAttachment::BeginPlay()
{
	Super::BeginPlay();
	
	//오너 캐릭터 가져오기
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	//Holster에 무기 부착
	AttachTo(HolsterSocketName);
}



//Equip을 마무리하고 무기를 손에 장비
void AWeaponAttachment::EndEquip()
{
	AttachTo(EquipSocketName);
}


//UnEquip을 마무리하고 무기를 장비 해제
void AWeaponAttachment::EndUnEquip()
{
	AttachTo(HolsterSocketName);
}


//소켓에 액터를 붙임
void AWeaponAttachment::AttachTo(FName InSocketName)
{
	if(InSocketName.IsNone())
	{
		return;
	}
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}