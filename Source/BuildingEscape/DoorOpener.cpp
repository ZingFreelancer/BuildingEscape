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
}


// Called when the game starts
void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if ((GetTotalMassInsideTrigger() > 80.0f) && !DoorIsOpen) //TODO Expose treshold mass to editor
	{
		DoorIsOpen = true;
		OnOpen.Broadcast();
	}
	else if (DoorIsOpen && GetTotalMassInsideTrigger() < 80.0f) //Check if door should be closed
	{
		OnClose.Broadcast();
		DoorIsOpen = false;
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
