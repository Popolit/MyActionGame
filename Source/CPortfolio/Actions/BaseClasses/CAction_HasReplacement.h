#pragma once

#include "CoreMinimal.h"
#include "CAction_Base.h"
#include "IKeyInput.h"
#include "CAction_HasReplacement.generated.h"

class UCAction_Replacement;

//어떤 조건 트리거 시, 다른 액션으로 자신을 대체
//예시 : 일반 좌클릭 = 평타, 달리기 중엔 좌클릭이 대쉬 어택으로 대체
UCLASS(Abstract, HideDropdown)
class CPORTFOLIO_API UCAction_HasReplacement : public UCAction_Base, public IIKeyInput
{
	GENERATED_BODY()

public:
	UCAction_HasReplacement();

public:
	virtual void BeginPlay() override;
	virtual void EndAction() override;
	virtual void KeyPressed() override final;
	virtual void KeyReleased() override final;

private:
	virtual void HandleKeyPressed() {} //KeyPressed 실질적 구현
	virtual void HandleKeyReleased() {} //KeyReleased 실질적 구현
	
private:
	void ReplaceAction(UCAction_Base* InAction);
	void RevertAction();
	
protected:
	UPROPERTY(EditDefaultsOnly)
		TMap<FName, TSubclassOf<UCAction_Replacement>> ClassOfActionsToReplace;
	UPROPERTY()
		TArray<UCAction_Replacement*> ActionsToReplace;
private:
	UCAction_Base* SubjectAction;
};
