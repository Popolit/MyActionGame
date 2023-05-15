#include "WeaponAttachment.h"

#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"

/* Collision ä���� �߰��ϵ��� ���� �ʿ� */
AWeaponAttachment::AWeaponAttachment() : HolsterSocketName("Root"), EquipSocketName("Root")
{
	Root = this->CreateDefaultSubobject<USceneComponent>("Root");
	this->SetRootComponent(Root);
}

void AWeaponAttachment::BeginPlay()
{
	Super::BeginPlay();
	
	//���� ĳ���� ��������
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	//Holster�� ���� ����
	AttachTo(HolsterSocketName);
}



//Equip�� �������ϰ� ���⸦ �տ� ���
void AWeaponAttachment::EndEquip()
{
	AttachTo(EquipSocketName);
}


//UnEquip�� �������ϰ� ���⸦ ��� ����
void AWeaponAttachment::EndUnEquip()
{
	AttachTo(HolsterSocketName);
}


//���Ͽ� ���͸� ����
void AWeaponAttachment::AttachTo(FName InSocketName)
{
	if(InSocketName.IsNone())
	{
		return;
	}
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}