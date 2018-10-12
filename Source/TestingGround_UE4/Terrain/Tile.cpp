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

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	SphereCast(GetActorLocation(), 300);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn,int32 MinNum,int32 MaxNum)
{
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);
	int32 NumberToSpawn = FMath::RandRange(MinNum,MaxNum);

	for (int32 i = 1; i <= NumberToSpawn; i++)
	{
		FVector SpawnPoint = FMath::RandPointInBox(Bounds);
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn);
		SpawnedActor->SetActorRelativeLocation(SpawnPoint);
		SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	}
}

bool ATile::SphereCast(FVector Location, float Radius)
{
	FHitResult Hit;
	bool HitResult = GetWorld()->SweepSingleByChannel(Hit, Location, Location, FQuat::Identity, ECollisionChannel::ECC_Camera, FCollisionShape::MakeSphere(Radius));

	FColor ColorResult = HitResult ? FColor::Red : FColor::Green;
	DrawDebugSphere(GetWorld(), Location, Radius, 100, ColorResult, true, 100);


	return HitResult;

}