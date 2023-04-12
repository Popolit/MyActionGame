#include "CAIController.h"
#include "CHelpers.h"

#include "CCharacter_Base.h"
#include "Components/CAIBehaviorComponent.h"

#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

ACAIController::ACAIController(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("CrowdFollowingComponent")))
{
	CHelpers::CreateActorComponent<UAIPerceptionComponent>(this, &Perception, "Perception");
	CHelpers::CreateActorComponent<UBlackboardComponent>(this, &Blackboard, "Blackboard");

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	Sight->SightRadius = 600;
	Sight->LoseSightRadius = 800;
	Sight->PeripheralVisionAngleDegrees = 60;
	Sight->SetMaxAge(2);

	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;

	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(*Sight->GetSenseImplementation());
}

void ACAIController::BeginPlay()
{
	Super::BeginPlay();

	Perception->OnPerceptionUpdated.AddDynamic(this, &ACAIController::OnPerceptionUpdated);
}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwnerCharacter = Cast<ACCharacter_Base>(InPawn);
	SetGenericTeamId(OwnerCharacter->GetGenericTeamId());
	
	BehaviorComponent = CHelpers::GetComponent<UCAIBehaviorComponent>(OwnerCharacter);
	check(BehaviorComponent);

	UseBlackboard(BehaviorComponent->GetBehaviorTree()->GetBlackboardAsset(), Blackboard);
	BehaviorComponent->SetBlackboard(Blackboard);

	RunBehaviorTree(BehaviorComponent->GetBehaviorTree());
}

void ACAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> Actors;
	Perception->GetCurrentlyPerceivedActors(nullptr, Actors);

	if(Actors.IsValidIndex(0))
	{
		Blackboard->SetValueAsObject("Target", Cast<ACCharacter_Base>(Actors[0]));
	}
	else
	{
		Blackboard->SetValueAsObject("Target", nullptr);
	}
}