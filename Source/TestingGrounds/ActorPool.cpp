// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorPool.h"


// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AActor * UActorPool::Checkout()
{
	if (ArrayPool.Num() == 0) return nullptr;
	return ArrayPool.Pop();
}

void UActorPool::Add(AActor * ActorToReturn)
{

	ArrayPool.Push(ActorToReturn);

}
