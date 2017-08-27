// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorOpener.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UDoorOpener::UDoorOpener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();
	//Find the owning actor
	AActor *Owner = GetOwner();
	//Create rotator
	FRotator NewDoorRotation(0.0f, 70.0f, 0.0f);
	//Set door rotation
	Owner->SetActorRotation(NewDoorRotation);
}


// Called every frame
void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

