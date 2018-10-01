
// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWayPoint.h"


EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Getting Patrol Routes
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	UPatrolRoute* PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();

	if (!PatrolRoute)  //If PatrolPoint Component Doesnt Exist
		return EBTNodeResult::Failed;


	TArray<AActor*> PatrollingPoints = PatrolRoute->GetPatrolPoints();
	if (PatrollingPoints.Num() == 0)  //If No Patrol Points Are Assigned
	{
		UE_LOG(LogTemp, Warning, TEXT("Guard Missing Patrol Points"));
		return EBTNodeResult::Failed;
	}
	//Set Way Point
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	int Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WayPointKey.SelectedKeyName,PatrollingPoints[Index]);

	//Cycle The Index
	
	int NewIndex = (Index+1) % PatrollingPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NewIndex);

	

	//UE_LOG(LogTemp, Warning, TEXT("Waypoint Index: %i "),Index);
	return EBTNodeResult::Succeeded;
 }

