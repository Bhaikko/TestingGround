// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "ActorPool.h"
#include "Engine/World.h"
#include "AI/Navigation/NavigationSystem.h"
#include "GameFramework/Pawn.h"
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

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinNum, int32 MaxNum, float Radius, float MinScale, float MaxScale)
{
	TArray<FSpawnPosition> SpawnPositions=RandomSpawnPoints(MinNum,MaxNum,Radius,MinScale,MaxScale);

	for (FSpawnPosition Position : SpawnPositions)
	{
		SpawnActor(ToSpawn, Position);
	}
	
}
TArray<FSpawnPosition> ATile::RandomSpawnPoints(int32 MinNum, int32 MaxNum, float Radius, float MinScale, float MaxScale)
{
	TArray<FSpawnPosition> SpawnPositions;
	int32 NumberToSpawn = FMath::RandRange(MinNum, MaxNum);

	for (int32 i = 1; i <= NumberToSpawn; i++)
	{
		FSpawnPosition SpawnPosition;

		SpawnPosition.Rotation = FMath::RandRange(-180.0f, 180.0f);
		SpawnPosition.Scale = FMath::RandRange(MinScale, MaxScale);
		if (FindEmptyLocation(SpawnPosition.Location, Radius*SpawnPosition.Scale))
			SpawnPositions.Add(SpawnPosition);

	}

	return SpawnPositions;

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

void ATile::SpawnActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition& SpawnPosition)
{
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn);
	SpawnedActor->SetActorRelativeLocation(SpawnPosition.Location);
	SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	SpawnedActor->SetActorRelativeRotation(FRotator(0, SpawnPosition.Rotation, 0));
	SpawnedActor->SetActorRelativeScale3D(FVector(SpawnPosition.Scale));
}
void ATile::PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int32 MinNum, int32 MaxNum, float Radius)
{
	TArray<FSpawnPosition> SpawnPositions = RandomSpawnPoints(MinNum, MaxNum, Radius, 1, 1);

	for (FSpawnPosition Position : SpawnPositions)
	{
		SpawnAIPawns(ToSpawn, Position);
	}
	

}

void ATile::SpawnAIPawns(TSubclassOf<AActor> ToSpawn, const FSpawnPosition& SpawnPosition)
{
	APawn* SpawnedAI = GetWorld()->SpawnActor<APawn>(ToSpawn);
	SpawnedAI->SetActorRelativeLocation(SpawnPosition.Location);
	SpawnedAI->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	SpawnedAI->SetActorRelativeRotation(FRotator(0, SpawnPosition.Rotation, 0));
	SpawnedAI->SpawnDefaultController();
	SpawnedAI->Tags.Add(FName("Enemy"));
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
		return;
	
	NavMeshVolume->SetActorLocation(GetActorLocation());

	UNavigationSystem::GetNavigationSystem(GetWorld())->Build();

	

}