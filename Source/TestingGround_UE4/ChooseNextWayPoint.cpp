
// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWayPoint.h"


EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Getting Patrol Routes
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* ControlledPawn = AIController->GetPawn();
	APatrollingGuard* PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	TArray<AActor*> PatrollingPoints = PatrollingGuard->PatrolPointsCpp;
	if (PatrollingPoints[0] == nullptr)
		return EBTNodeResult::Succeeded;

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

