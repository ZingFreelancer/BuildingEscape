// Fill out your copyright notice in the Description page of Project Settings.
#include "Grabber.h"
#include "Engine/World.h"
#include "Gameframework/Actor.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector OUT PlayerViewPointLocation;
	FRotator OUT PlayerViewPointRoration;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRoration);
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRoration.Vector() * ViewReach;
	///UE_LOG(LogTemp, Warning, TEXT("Position: %s, Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRoration.ToString());
	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor::Green, false, 0.0f, 25);

	///Line trace parameters
	FHitResult OUT HitResult;
	FCollisionQueryParams CollisionQueryParams(FName(TEXT("")), false, GetOwner());
	//Line tracing (ray casting) out to reach distance
	GetWorld()->LineTraceSingleByObjectType(HitResult, PlayerViewPointLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), CollisionQueryParams);

	//Print what you are hitting
	if (HitResult.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Trace hit: %s"), *HitResult.Actor->GetName());
	}
	
}

