#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"

/* Static Helper Class for Unreal Engine */
class CHELPERS_API CHelpers
{
public:
	/**
	 * 컴포넌트 생성 후 Actor에 종속
	 * @param InActor 부모 액터
	 * @param OutComponent 생성될 컴포넌트
	 * @param InName 컴포넌트의 이름
	 * @param InParent 컴포넌트를 종속시킬 씬 컴포넌트 (없으면 Root)
	 */
	template<typename T>
	static void CreateComponent(AActor* InActor, T** OutComponent, FName InName, USceneComponent* InParent = nullptr)
	{
		*OutComponent = InActor->CreateDefaultSubobject<T>(InName);

		if (InParent != nullptr)
		{
			(*OutComponent)->SetupAttachment(InParent);

			return;
		}

		InActor->SetRootComponent(*OutComponent);
	}

	/**
	 * 액터 컴포넌트의 생성
	 * @param InActor 부모 액터
	 * @param OutComponent 생성될 컴포넌트
	 * @param InName 컴포넌트의 이름
	 */
	template<typename T>
	static void CreateActorComponent(AActor* InActor, T** OutComponent, FName InName)
	{
		*OutComponent = InActor->CreateDefaultSubobject<T>(InName);
	}

	/**
	 * Actor에게서 컴포넌트를 가져옴
	 * @param InActor 대상 액터
	 */
	template<typename T>
	static T* GetComponent(AActor* InActor)
	{
		return Cast<T>(InActor->GetComponentByClass(T::StaticClass()));
	}

	/**
	 * Actor에게서 컴포넌트를 가져옴
	 * @param InActor 대상 액터
	 * @param InName 대상 컴포넌트의 이름
	 */
	template<typename T>
	static T* GetComponent(AActor* InActor, const FString& InName)
	{
		TArray<T *> components;
		InActor->GetComponents<T>(components);

		for (T* component : components)
		{
			if (component->GetName() == InName)
			{
				return component;
			}
		}

		return nullptr;
	}
};