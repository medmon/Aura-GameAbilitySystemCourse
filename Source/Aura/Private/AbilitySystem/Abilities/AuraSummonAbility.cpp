// Copyright © 2023 Jodiah Jensen


#include "AbilitySystem/Abilities/AuraSummonAbility.h"

#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnSpread / (NumMinions-1);

	const FVector RightOfSpread = Forward.RotateAngleAxis(SpawnSpread / 2.0f, FVector::UpVector);
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread / 2.0f, FVector::UpVector);

	TArray<FVector> SpawnLocations;
	for (int32 i = 0; i < NumMinions; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		FVector ChosenSpawnLoc = Location + Direction * FMath::FRandRange(MinSpawnDist, MaxSpawnDist);

		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, ChosenSpawnLoc + FVector(0.f,0.f,400.f), ChosenSpawnLoc - FVector(0.f,0.f,400.f), ECC_Visibility);
		if (Hit.bBlockingHit)
		{
			ChosenSpawnLoc = Hit.ImpactPoint;
		}
		
		SpawnLocations.Add(ChosenSpawnLoc);
		
		// DrawDebugSphere(GetWorld(), ChosenSpawnLoc, 15.f, 12, FColor::Cyan, false, 3.f);
		//
		// UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Location, Location + Direction * MaxSpawnDist, 4.f, FLinearColor::Gray, 3.f);
		//
		// DrawDebugSphere(GetWorld(), Location + Direction * MinSpawnDist, 5.f, 12, FColor::Red, false, 3.f);
		// DrawDebugSphere(GetWorld(), Location + Direction * MaxSpawnDist, 5.f, 12, FColor::Red, false, 3.f);

	}

	
	return SpawnLocations;
	
}

TSubclassOf<APawn> UAuraSummonAbility::GetRandomMinionClass()
{
	const int32 Selection = FMath::RandRange(0, MinionClasses.Num()-1);
	return MinionClasses[Selection];
}
