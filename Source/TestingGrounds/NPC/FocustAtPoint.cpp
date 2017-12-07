// Fill out your copyright notice in the Description page of Project Settings.

#include "FocustAtPoint.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/World.h"


EBTNodeResult::Type UFocustAtPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	
	if (FocusKey.IsSet())
	{
		OwnerComp.GetAIOwner()->SetFocus(Cast<AActor>(BlackBoardComp->GetValueAsObject(FocusKey.SelectedKeyName)));
		return EBTNodeResult::Succeeded;
	}
	else {
		return EBTNodeResult::Failed;
	}

}
