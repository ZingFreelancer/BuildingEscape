// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorOpener.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

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
	ActorWhoCanOpenDoor = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UDoorOpener::ActorEndOverlap(AActor * Self, AActor * OtherActor)
{
	CloseDoor();
}

void UDoorOpener::CloseDoor()
{
	//Close door
	UE_LOG(LogTemp, Warning, TEXT("Close the god damn door!"));
	GetOwner()->SetActorRotation(FRotator(0,0,0));
}

void UDoorOpener::OpenDoor()
{
	DoorIsOpen = true;
	//Find the owning actor
	AActor *Owner = GetOwner();
	//Create rotator
	FRotator NewDoorRotation(0.0f, OpenAngle, 0.0f);
	UE_LOG(LogTemp, Warning, TEXT("Open the god damn door!"));
	//Set door rotation
	Owner->SetActorRotation(NewDoorRotation);
}




// Called every frame
void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if the actor that opens is in the volume, open the door
	if (PressurePlate->IsOverlappingActor(ActorWhoCanOpenDoor) && !DoorIsOpen)
	{
		OpenDoor();
	}
}

