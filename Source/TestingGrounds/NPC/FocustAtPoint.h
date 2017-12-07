// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FocustAtPoint.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API UFocustAtPoint : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
		struct FBlackboardKeySelector FocusKey;
	
	
};
