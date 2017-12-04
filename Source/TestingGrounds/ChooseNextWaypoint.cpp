// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingComponent.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UPatrollingComponent* Component = OwnerComp.GetAIOwner()->GetPawn()->FindComponentByClass<UPatrollingComponent>();
	if (!ensure(Component)) return EBTNodeResult::Failed;

	TArray<AActor*> PatrolPoints = Component->GetPatrolPoints();
	if(PatrolPoints.Num() == 0){ 
		UE_LOG(LogTemp, Warning, TEXT("No patrol points"))
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	int32 Index = BlackBoardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackBoardComp->SetValueAsObject(WayPointKey.SelectedKeyName, PatrolPoints[Index]);
	BlackBoardComp->SetValueAsInt(IndexKey.SelectedKeyName, (Index + 1) % PatrolPoints.Num());
	
	return EBTNodeResult::Succeeded;

}
