// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <memory>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyRTTITryStaticNegPluginActor.generated.h"

namespace myrtti_AMyRTTITryStaticNegPluginActor
{
	struct Context;
}

UCLASS()
class MYRTTIBENCHMARKACTORS_API AMyRTTITryStaticNegPluginActor : public AActor
{
	GENERATED_BODY()

	myrtti_AMyRTTITryStaticNegPluginActor::Context* ctx;

public:
	// Sets default values for this actor's properties
	AMyRTTITryStaticNegPluginActor();
	~AMyRTTITryStaticNegPluginActor() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
