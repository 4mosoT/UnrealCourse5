// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrollingComponent.generated.h"

/*Component that controls the route points
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTINGGROUNDS_API UPatrollingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	TArray<AActor*> GetPatrolPoints() const;

public:	


	UPROPERTY(EditAnywhere, Category = "Patrol Route")
		TArray<AActor*> PatrolPoints;
		
	
};
