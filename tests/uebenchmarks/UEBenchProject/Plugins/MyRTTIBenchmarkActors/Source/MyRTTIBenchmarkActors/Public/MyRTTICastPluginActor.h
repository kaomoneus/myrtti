// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <memory>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyRTTICastPluginActor.generated.h"

namespace myrtti_AMyRTTICastPluginActor
{
	struct Context;
}

UCLASS()
class MYRTTIBENCHMARKACTORS_API AMyRTTICastPluginActor : public AActor
{
	GENERATED_BODY()

	myrtti_AMyRTTICastPluginActor::Context* ctx;
	
public:
	// Sets default values for this actor's properties
	AMyRTTICastPluginActor();
	~AMyRTTICastPluginActor() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
