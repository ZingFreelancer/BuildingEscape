// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "Gameframework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"
#include "CollisionQueryParams.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	//Get this actor physics handle
	FindActorPhysicsHandle();
	//Setup input for physics handle
	SetupInputComponent();
}

//Sets InputComponent to handle Grab pressed and released events
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		///Bind input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::GrabItem);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::ReleaseItem);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find UInputComponent on %s"), *GetOwner()->GetName());
	}
}

//Tries to locate actor physics handle component, writes error if it fails
void UGrabber::FindActorPhysicsHandle()
{
	///Get physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find UPhysicsCollisionHandler on %s"), *GetOwner()->GetName());
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PhysicsHandle && PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetLineTraceEnd());
	}
	
}

FVector UGrabber::GetLineTraceStart()
{
	FVector OUT PlayerViewPointLocation;
	FRotator OUT PlayerViewPointRoration;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRoration);
	return PlayerViewPointLocation;
}

FVector UGrabber::GetLineTraceEnd()
{
	FVector OUT PlayerViewPointLocation;
	FRotator OUT PlayerViewPointRoration;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRoration);
	return (PlayerViewPointLocation + PlayerViewPointRoration.Vector() * ViewReach);
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	///Line trace parameters
	FHitResult OUT HitResult;
	FCollisionQueryParams CollisionQueryParams(FName(TEXT("")), false, GetOwner());
	///Line tracing (ray casting) out to reach distance
	GetWorld()->LineTraceSingleByObjectType(HitResult, GetLineTraceStart(), GetLineTraceEnd(), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), CollisionQueryParams);
	return HitResult;
}

//Grab object within reach
void UGrabber::GrabItem()
{
	auto HitBodyInreach = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitBodyInreach.GetComponent();
	auto ActorHit = HitBodyInreach.GetActor();
	if(ActorHit && PhysicsHandle)
		PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
}

//Release grabbed object
void UGrabber::ReleaseItem()
{
	if(PhysicsHandle)
		PhysicsHandle->ReleaseComponent();
}

