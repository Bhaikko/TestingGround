// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "ActorPool.h"
#include "Engine/World.h"
#include "AI/Navigation/NavigationSystem.h"
#include "DrawDebugHelpers.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MinExtend = FVector(0, -2000, 0);
	MaxExtend = FVector(4000, 2000, 0);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	Pool->Return(NavMeshVolume);
	

}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn,int32 MinNum,int32 MaxNum,float Radius,float MinScale,float MaxScale)
{
	int32 NumberToSpawn = FMath::RandRange(MinNum,MaxNum);

	for (int32 i = 1; i <= NumberToSpawn; i++)
	{
		FVector SpawnPoint;
		float RandomRotation = FMath::RandRange(-180.0f, 180.0f);
		float RandomScale = FMath::RandRange(MinScale, MaxScale);
		if(FindEmptyLocation(SpawnPoint,Radius*RandomScale))
			SpawnActor(ToSpawn, SpawnPoint,RandomRotation,RandomScale);
		
	}
}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult Hit;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	bool HitResult = GetWorld()->SweepSingleByChannel(Hit, GlobalLocation, GlobalLocation, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));
	return !HitResult;

}

bool ATile::FindEmptyLocation(FVector& SpawnPoint,float Radius)
{

	FBox Bounds(MinExtend, MaxExtend);
	int32 MaxAttempts = 5;
	for (int i = 1; i <= MaxAttempts; i++)
	{
		SpawnPoint = FMath::RandPointInBox(Bounds);
		if (CanSpawnAtLocation(SpawnPoint, Radius))
			return true;
	}

	return false;
}

void ATile::SpawnActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint,float Rotation,float Scale)
{
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn);
	SpawnedActor->SetActorRelativeLocation(SpawnPoint);
	SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	SpawnedActor->SetActorRelativeRotation(FRotator(0, Rotation, 0));
	SpawnedActor->SetActorRelativeScale3D(FVector(Scale));
}

void ATile::PoolReference(UActorPool* PoolToSet)
{
	Pool = PoolToSet;
	
	PositionNavmeshVolume();
}

void ATile::PositionNavmeshVolume()
{
	
	NavMeshVolume = Pool->Checkout();
	if (NavMeshVolume == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Navmesh Null"));
		return;
	}
	NavMeshVolume->SetActorLocation(GetActorLocation());

	UNavigationSystem::GetNavigationSystem(GetWorld())->Build();
	UE_LOG(LogTemp, Warning, TEXT("Repositioned"));
	

}