// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Items/Manifest/Inv_ItemManifest.h"
#include "Inv_InventoryItem.generated.h"

/**
 * Inventory Data Item
 */
UCLASS()
class INVENTORY_API UInv_InventoryItem : public UObject {
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool IsSupportedForNetworking() const override { return true; }
	
	void SetItemManifest(const FInv_ItemManifest& Manifest);
	const FInv_ItemManifest& GetItemManifest() const { return ItemManifest.Get<FInv_ItemManifest>(); }
	FInv_ItemManifest& GetItemManifestMutable() { return ItemManifest.GetMutable<FInv_ItemManifest>(); }
	
private:
	
	// INSTANCED STRUCTS: struct is instanced along with its owner, can be used polymorphically, can be exposed to Blueprint, 
	// without the performance overhead of UObject pointers.
	UPROPERTY(VisibleAnywhere, Replicated, meta=(BaseStruct="/Script/Inventory.Inv_ItemManifest"), Category = "Inventory")
	FInstancedStruct ItemManifest;
};

template<typename TFragmentType>
const TFragmentType* GetFragment(const UInv_InventoryItem* Item, const FGameplayTag& Tag)
{
	if (!IsValid(Item)) return nullptr;
	const FInv_ItemManifest& Manifest = Item->GetItemManifest();
	return Manifest.GetFragmentOfTypeWithTag<TFragmentType>(Tag);
}