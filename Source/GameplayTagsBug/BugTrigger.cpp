

#include "BugTrigger.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemBlueprintLibrary.h"

ABugTrigger::ABugTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComp);
}

void ABugTrigger::BeginPlay()
{
	Super::BeginPlay();
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if(HasAuthority())
	{
		TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBoxBeginOverlap);
		TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnBoxEndOverlap);
	}
}

void ABugTrigger::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSeep, const FHitResult& SweepResult)
{
	if (UAbilitySystemComponent* AbilitySysComp = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
	{
		FGameplayTagContainer TagContainer(FGameplayTag::RequestGameplayTag("Debug.Test"));
		UAbilitySystemBlueprintLibrary::AddLooseGameplayTags(OtherActor, TagContainer, true);
	}
}

void ABugTrigger::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	FGameplayTagContainer TagContainer(FGameplayTag::RequestGameplayTag("Debug.Test"));
	UAbilitySystemBlueprintLibrary::RemoveLooseGameplayTags(OtherActor, TagContainer, true);
}

