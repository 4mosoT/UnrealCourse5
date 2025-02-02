// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()
	FVector Location;
	float Rotation;
	float Scale;

};

class UActorPool;

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable)
		void PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float Radius = 500, float MinScale = 1, float MaxScale = 1 );

	UFUNCTION(BlueprintCallable)
		void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float Radius = 500);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = Spawning)
		FVector MinExtend; 
	UPROPERTY(EditDefaultsOnly, Category = Spawning)
		FVector MaxExtend;

	UPROPERTY(EditDefaultsOnly, Category = Navigation)
		FVector NavigationBoundsOffset;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Pool)
	void SetPool(UActorPool* NavMeshBoundsVolumePool);

private:

	bool CanSpawnAtLocation(FVector Location, float Radius);
	UActorPool* NavMeshBoundsVolumePool;

	AActor* NavMeshBoundsVolume = nullptr;

	TArray<FSpawnPosition> GeneratePositionsArray(int32 MinScale, int32 MaxScale, int32 NumberOfPositions);

	TArray<AActor*> ActorsList;

};
