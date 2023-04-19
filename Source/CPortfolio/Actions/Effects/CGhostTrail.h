#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CGhostTrail.generated.h"

class UPoseableMeshComponent;

/* 액션 캔슬 시 잔상이 남는 GhostTrail Effect 클래스 */
UCLASS()
class CPORTFOLIO_API ACGhostTrail : public AActor
{
	GENERATED_BODY()
	
public:	
	ACGhostTrail();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Capture")
		float LifeSpan = 1.0f;	//전체 지속 시간
	
	UPROPERTY(EditDefaultsOnly, Category = "Capture")
		float StartDelay = 0;	//해당 시간 후 부터 이펙트 시작
	
	UPROPERTY(EditDefaultsOnly, Category = "Capture")
		float Interval = 0.25f;	//이펙트 갱신 간격
	
	UPROPERTY(EditDefaultsOnly, Category = "Material")
		class UMaterialInstanceConstant* MaterialInstance;

	UPROPERTY(EditDefaultsOnly, Category = "Material")
		FLinearColor Color = FLinearColor(1, 1, 1, 1);	//이펙트 색상
	
	UPROPERTY(EditDefaultsOnly, Category = "Material")
		float Exp = 1;	// 투명도


private:
	UPROPERTY(VisibleDefaultsOnly)
		UPoseableMeshComponent* Mesh;
	
private:
	ACharacter* OwnerCharacter;
	UMaterialInstanceDynamic* Material;
	
	FTimerHandle TimerHandle;
};
