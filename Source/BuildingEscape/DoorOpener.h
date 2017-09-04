// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "DoorOpener.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UDoorOpener : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpener();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void ActorEndOverlap(class AActor* Self, class AActor* OtherActor);
	void CloseDoor();
	void OpenDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	bool DoorIsOpen = false;
	float LastDoorOpenTimer = 0;

	UPROPERTY(EditAnywhere)float OpenAngle = 80.0f;
	UPROPERTY(EditAnywhere)float DoorCloseDelay = 1.0f;
	UPROPERTY(EditAnywhere)ATriggerVolume* PressurePlate;
	AActor* ActorWhoCanOpenDoor;
};
