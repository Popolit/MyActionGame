#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Struct/FeetData.h"
#include "CFeetComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTFOLIO_API UCFeetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCFeetComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE const FFeetData& GetData() { return FeetData; }
private:
	void Trace(FName const& InSocketName, float& OutLocation, FRotator& OutRotator);
	void ApplyIK(float DeltaTime);

private:
	class ACCharacter_Base* Owner;
	
	FFeetData FeetData;

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "FeetIK")
		FName LeftFootName = "foot_l";;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "FeetIK")
		FName RightFootName = "foot_r";;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "FeetIK")
		float TraceDistance = 100.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "FeetIK")
		float InterpSpeed = 60.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "FeetIK")
		float OffsetDistance = 5.0f;
};
