// Fill out your copyright notice in the Description page of Project Settings.

#include "MyRTTITryStaticNegPluginActor.h"

#include "myrtti_utils.h"
#include "UEBenchmarkHierarchy/myrtti_Deep.h"

namespace myrtti_AMyRTTITryStaticNegPluginActor
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
AMyRTTITryStaticNegPluginActor::AMyRTTITryStaticNegPluginActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ctx = new myrtti_AMyRTTITryStaticNegPluginActor::Context();
}

AMyRTTITryStaticNegPluginActor::~AMyRTTITryStaticNegPluginActor()
{
	delete ctx;
}


// Called when the game starts or when spawned
void AMyRTTITryStaticNegPluginActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyRTTITryStaticNegPluginActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i = 0; i!=CASTS_PER_TICK;++i)
	{
		auto *res = myrtti::try_static_cast<MyRTTI_Deep_1_v2*>(ctx->basePtr);
		check(res == nullptr);
		DoNotOptimize(res);
	}
}

