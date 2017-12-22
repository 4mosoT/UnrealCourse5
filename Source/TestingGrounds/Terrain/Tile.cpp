// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "ActorPool.h"
#include "AI/Navigation/NavigationSystem.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MinExtend = FVector(0, -2000, 0);
	MaxExtend = FVector(4000, 2000, 0);
	NavigationBoundsOffset = FVector(2000, 0, 0);

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn , int32 MaxSpawn, float Radius, float MinScale, float MaxScale)
{

	int32 SpawnNumber = FMath::RandRange(MinSpawn, MaxSpawn);
	FVector SpawnPoint;
	for (size_t i =0 ; i < SpawnNumber; i++)
	{
		for (size_t t = 0; t < 20; t++)
		{
			SpawnPoint = FMath::RandPointInBox(FBox(MinExtend, MaxExtend));
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

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] End Play"), *GetName())
	NavMeshBoundsVolumePool->Add(NavMeshBoundsVolume);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::SetPool(UActorPool * NavMeshBoundsVolumePool)
{
	this->NavMeshBoundsVolumePool = NavMeshBoundsVolumePool;
	
	NavMeshBoundsVolume = NavMeshBoundsVolumePool->Checkout();
	if (NavMeshBoundsVolume == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("[s%] Not Enough Actors In Pool"), *GetName());
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("[%s] Checkout: [%s] "), *GetName(), *NavMeshBoundsVolume->GetName());
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavigationBoundsOffset);
	GetWorld()->GetNavigationSystem()->Build();
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

