// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float Radius)
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
			if (CanSpawnAtLocation(SpawnPoint, Radius)) {
				AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
				Spawned->SetActorRelativeLocation(SpawnPoint);
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
	
	FColor Color = Result ? FColor::Red : FColor::Green;
	DrawDebugSphere(GetWorld(), GlobalLocation, Radius, 8, Color, true, 1000);

	return !Result;

}

