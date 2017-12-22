// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Engine/StaticMesh.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn , int32 MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	int32 SpawnNumber = FMath::RandRange(MinSpawn, MaxSpawn);
	FVector SpawnPoint;
	for (size_t i =0 ; i < SpawnNumber; i++)
	{
		for (size_t t = 0; t < 20; t++)
		{
			SpawnPoint = FMath::RandPointInBox(FBox(Min, Max));
			float Scale = FMath::RandRange(MinScale, MaxScale);
			if (CanSpawnAtLocation(SpawnPoint, Radius * Scale)) {
				AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
				Spawned->SetActorRelativeLocation(SpawnPoint);
				Spawned->SetActorRotation(FRotator(0, FMath::RandRange(-180.f, 180.f), 0));
				Spawned->SetActorScale3D(FVector(Scale));
				Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
				break;
			}
		}

	}
}



// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::SetPool(UActorPool * NavMeshBoundsVolumePool)
{
	this->NavMeshBoundsVolumePool = NavMeshBoundsVolumePool;
}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	bool Result =  GetWorld()->SweepSingleByChannel(
		HitResult,
		GlobalLocation,
		GlobalLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius)
	);
	
	return !Result;

}

