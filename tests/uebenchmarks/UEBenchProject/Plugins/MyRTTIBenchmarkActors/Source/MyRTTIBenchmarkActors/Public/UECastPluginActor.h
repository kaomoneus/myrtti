// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <memory>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UECastPluginActor.generated.h"

namespace myrtti_uebench
{
	struct UEActorContext;
}

UCLASS()
class MYRTTIBENCHMARKACTORS_API AUECastPluginActor : public AActor
{
	GENERATED_BODY()

	myrtti_uebench::UEActorContext* ctx;
	
public:
	// Sets default values for this actor's properties
	AUECastPluginActor();
	~AUECastPluginActor() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
