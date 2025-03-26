// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "BugTrigger.generated.h"

UCLASS()
class GAMEPLAYTAGSBUG_API ABugTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ABugTrigger();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSeep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere)
	UBoxComponent* TriggerBox;

	UPROPERTY()
	USceneComponent* RootComp;

};
