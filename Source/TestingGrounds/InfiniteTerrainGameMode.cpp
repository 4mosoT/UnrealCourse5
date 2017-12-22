// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"


AInfiniteTerrainGameMode::AInfiniteTerrainGameMode() {

	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(FName("Nav Mesh Volume Pool"));

}


void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume* NavMeshVolume) {

	UE_LOG(LogTemp, Warning, TEXT("Volume Added: %s"), *NavMeshVolume->GetName())
	NavMeshBoundsVolumePool->Add(NavMeshVolume);
}

void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	TActorIterator<ANavMeshBoundsVolume> NavMeshIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (NavMeshIterator) {
		AddToPool(*NavMeshIterator);
		++NavMeshIterator;
	}
}
