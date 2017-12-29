// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestingGroundsGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

class ANavMeshBoundsVolume;
class UActorPool;
/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API AInfiniteTerrainGameMode : public ATestingGroundsGameMode
{
	GENERATED_BODY()
	
public: 
	AInfiniteTerrainGameMode();

	UFUNCTION(BlueprintCallable, Category = "Scoring")
	void TileConquered();

	UFUNCTION(BlueprintCallable, Category = "Scoring")
	int GetScore();

private:
	void AddToPool(ANavMeshBoundsVolume* NavMeshVolume);

	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
	void PopulateBoundsVolumePool();

	int Score = 0;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pool")
		UActorPool* NavMeshBoundsVolumePool;
	
	
};
