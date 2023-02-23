#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "UObject/UnrealType.h"

// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(root);

	mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	mesh->SetupAttachment(root);
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(muzzleFlash, mesh, "MuzzleFlashSocket");

	APawn *ownerPawn = Cast<APawn>(GetOwner());
	if (ownerPawn == nullptr)
		return;
	AController *ownerController = ownerPawn->GetController();
	if (ownerController == nullptr)
		return;

	FVector location;
	FRotator rotation;
	ownerController->GetPlayerViewPoint(location, rotation);

	FVector end = location + rotation.Vector() * maxRange;

	FHitResult hit;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(GetOwner());

	bool bSucces = GetWorld()->LineTraceSingleByChannel(hit, location, end, ECollisionChannel::ECC_GameTraceChannel1, params);
	if (bSucces)
	{
		FVector shotDirection = -rotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), impactEffect, hit.Location, shotDirection.Rotation());

		AActor *hitActor = hit.GetActor();
		if (hitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(damage, hit, shotDirection, nullptr);
			hitActor->TakeDamage(damage, DamageEvent, ownerController, this);
		}
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
