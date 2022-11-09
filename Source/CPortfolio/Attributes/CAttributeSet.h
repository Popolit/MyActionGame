#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CAttributeSet.generated.h"

#define ATTRIBUTE_ACCESOR(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class CPORTFOLIO_API UCAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UCAttributeSet();

//  *********************
//      Attribute 贸府
//  *********************
public:
	virtual void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(BlueprintReadOnly, Category = "HP", ReplicatedUsing = OnRep_MaxHP)
		FGameplayAttributeData MaxHP;
		ATTRIBUTE_ACCESOR(UCAttributeSet, MaxHP);

	UPROPERTY(BlueprintReadOnly, Category = "HP", ReplicatedUsing = OnRep_CurrHP)
		FGameplayAttributeData CurrHP;
		ATTRIBUTE_ACCESOR(UCAttributeSet, CurrHP);

	UPROPERTY(BlueprintReadOnly, Category = "MP", ReplicatedUsing = OnRep_MaxMP)
		FGameplayAttributeData MaxMP;
		ATTRIBUTE_ACCESOR(UCAttributeSet, MaxMP);

	UPROPERTY(BlueprintReadOnly, Category = "MP", ReplicatedUsing = OnRep_CurrMP)
		FGameplayAttributeData CurrMP;
		ATTRIBUTE_ACCESOR(UCAttributeSet, CurrMP);

	UPROPERTY(BlueprintReadOnly, Category = "MP", ReplicatedUsing = OnRep_TickIncMP)
		FGameplayAttributeData TickIncMPAmount = 0.01f;
		ATTRIBUTE_ACCESOR(UCAttributeSet, TickIncMPAmount);
	
	UPROPERTY(BlueprintReadOnly, Category = "MoveSpeed", ReplicatedUsing = OnRep_MoveSpeed)
		FGameplayAttributeData MoveSpeed;
		ATTRIBUTE_ACCESOR(UCAttributeSet, MoveSpeed);

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
		FGameplayAttributeData Damage;
		ATTRIBUTE_ACCESOR(UCAttributeSet, Damage);

//  *********************
//      府敲府纳捞记
//  *********************
public:
	UFUNCTION()
		virtual void OnRep_MaxHP(const FGameplayAttributeData& OldValue);
	UFUNCTION()
		virtual void OnRep_CurrHP(const FGameplayAttributeData& OldValue);
	UFUNCTION()
		virtual void OnRep_MaxMP(const FGameplayAttributeData& OldValue);
	UFUNCTION()
		virtual void OnRep_CurrMP(const FGameplayAttributeData& OldValue);
	UFUNCTION()
		virtual void OnRep_TickIncMP(const FGameplayAttributeData& OldValue);
	UFUNCTION()
		virtual void OnRep_MoveSpeed(const FGameplayAttributeData& OldValue);
};
