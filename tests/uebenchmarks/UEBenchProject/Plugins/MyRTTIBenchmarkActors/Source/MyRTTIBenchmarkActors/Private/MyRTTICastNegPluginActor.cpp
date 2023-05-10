// Fill out your copyright notice in the Description page of Project Settings.

#include "MyRTTICastNegPluginActor.h"

#include "myrtti_utils.h"
#include "UEBenchmarkHierarchy/myrtti_Deep.h"

namespace myrtti_AMyRTTICastNegPluginActor
{
	struct Context
	{
		MyRTTI_Deep_19 instance;
		MyRTTI_Deep_1_v2 instanceWrong;
		MyRTTI_Deep_0*  basePtr = &instance;
		MyRTTI_Deep_19* finalPtr = &instance;
	};
}

// Sets default values
AMyRTTICastNegPluginActor::AMyRTTICastNegPluginActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ctx = new myrtti_AMyRTTICastNegPluginActor::Context();
}

AMyRTTICastNegPluginActor::~AMyRTTICastNegPluginActor()
{
	delete ctx;
}


// Called when the game starts or when spawned
void AMyRTTICastNegPluginActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyRTTICastNegPluginActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i = 0; i!=CASTS_PER_TICK;++i)
	{
		auto *res = ctx->basePtr->cast<MyRTTI_Deep_1_v2*>();
		check(res == nullptr);
		DoNotOptimize(res);
	}
}

