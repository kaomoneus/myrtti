// Fill out your copyright notice in the Description page of Project Settings.

#include "UECastPluginActor.h"

#include "myrtti_utils.h"
#include "UEBenchmarkHierarchy/UUnreal_Deep_19.h"
#include "UEBenchmarkHierarchy/UUnreal_Deep_1_v2.h"

namespace myrtti_AUECastPluginActor
{
	struct Context
	{
		UUnreal_Deep_19* finalPtr = NewObject<UUnreal_Deep_19>();
		UUnreal_Deep_1_v2* finalWrongPtr = NewObject<UUnreal_Deep_1_v2>();
		UUnreal_Deep_0*  basePtr = finalPtr;
	};
}

// Sets default values
AUECastPluginActor::AUECastPluginActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ctx = new myrtti_AUECastPluginActor::Context();
}

AUECastPluginActor::~AUECastPluginActor()
{
	delete ctx;
}


// Called when the game starts or when spawned
void AUECastPluginActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AUECastPluginActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i = 0; i!=CASTS_PER_TICK;++i)
	{
		auto *res = Cast<UUnreal_Deep_19>(ctx->basePtr);
		check(res != nullptr);
		DoNotOptimize(res);
	}	
}

