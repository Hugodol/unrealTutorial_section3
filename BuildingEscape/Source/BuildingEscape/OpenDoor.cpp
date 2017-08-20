// Copyright Hugo Dolemieux 2017

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT


UOpenDoor::UOpenDoor() {
	PrimaryComponentTick.bCanEverTick = true;
}


void UOpenDoor::BeginPlay() {
	Super::BeginPlay();
	Owner = GetOwner();
}


void UOpenDoor::OpenDoor() {
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}


void UOpenDoor::CloseDoor() {
	Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}


void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (GetTotalMassOFActorOnPlate() > 30.f) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay) {
		CloseDoor();
	}
}


float UOpenDoor::GetTotalMassOFActorOnPlate() {
	float TotalMass = 0.f;
	TArray <AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (const auto* Actor : OverlappingActors) {
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("Overlapping Actor: %s"), *Actor->GetName());
	}
	return TotalMass;
}
