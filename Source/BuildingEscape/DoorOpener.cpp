#include "DoorOpener.h"
#include "Components/PrimitiveComponent.h"
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
}

void UDoorOpener::ActorEndOverlap(AActor * Self, AActor * OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Actor end overlap"));
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
	////Create rotator
	//FRotator NewDoorRotation(0.0f, OpenAngle, 0.0f);
	//UE_LOG(LogTemp, Warning, TEXT("Open the god damn door!"));
	////Set door rotation
	//GetOwner()->SetActorRotation(NewDoorRotation);
	OnOpenRequest.Broadcast();
}

// Called every frame
void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if the actor that opens is in the volume, open the door
	if ((GetTotalMassInsideTrigger() > 80.0f) && !DoorIsOpen) //TODO Expose treshold mass to editor
	{
		DoorIsOpen = true;
		OpenDoor();
		LastDoorOpenTimer = GetWorld()->GetTimeSeconds();
	}
	else if (DoorIsOpen && GetTotalMassInsideTrigger() < 80.0f) //Check if door should be closed
	{
		if (GetWorld()->GetTimeSeconds() - LastDoorOpenTimer > DoorCloseDelay)	
		{
			CloseDoor();
			DoorIsOpen = false;
		}
	}
}

float UDoorOpener::GetTotalMassInsideTrigger()
{
	float TotalMass = 0.0f;
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("PressurePlate pointer missing!"));
		return 0;
	}
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (const AActor* A : OverlappingActors)
	{
		TotalMass += A->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	//TODO find all overlapping actors
	//Iterate through them and sum their masses
	OverlappingActors.Empty();
	return TotalMass;
}

//float ActorsMass = 0;
//TArray<UPrimitiveComponent*> comps;
//GetComponents(comps);
//for (auto Iter = comps.CreateConstIterator(); Iter; ++Iter)
//{
//	UPrimitiveComponent* comp = Cast<UPrimitiveComponent>(*Iter)
//		if (comp)
//		{
//			ActorsMass += comp->GetMass();
//		}
//}
