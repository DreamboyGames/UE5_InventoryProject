#pragma once

#include "Inv_GridTypes.generated.h"

class UInv_InventoryItem;

UENUM(BlueprintType)
enum class EInv_ItemCategory : uint8 {
	Equippable,
	Consumable,
	Craftable,
	None
};


USTRUCT()
struct FInv_SlotAvailability {
	GENERATED_BODY()
	
	FInv_SlotAvailability() {}
	FInv_SlotAvailability(int32 ItemIndex, int32 Room, bool bHasItem) : Index(ItemIndex), AmountToFill(Room), bItemAtIndex(bHasItem) {}
	
	int32 Index{INDEX_NONE};
	int32 AmountToFill{0};
	bool bItemAtIndex{false};
};

USTRUCT()
struct FInv_SlotAvailabilityResult {
	GENERATED_BODY()
	
	FInv_SlotAvailabilityResult() {}
	
	TWeakObjectPtr<UInv_InventoryItem> Item;
	int32 TotalRoomToFill{0};
	int32 Remainder{0};
	bool bStackable{false};
	TArray<FInv_SlotAvailability> SlotAvailabilities;
};


UENUM(BlueprintType)
enum class EInv_TileQuadrant : uint8 {
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight,
	None
};

USTRUCT(BlueprintType)
struct FInv_TileParameters {
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	FIntPoint TileCoordinates{};
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	int32 TileIndex{INDEX_NONE};
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	EInv_TileQuadrant TileQuadrant{EInv_TileQuadrant::None};
};

inline bool operator==(const FInv_TileParameters& a, const FInv_TileParameters& b)
{
	return a.TileCoordinates == b.TileCoordinates && a.TileIndex == b.TileIndex && a.TileQuadrant == b.TileQuadrant;
}


USTRUCT()
struct FInv_SpaceQueryResult {
	GENERATED_BODY()
	
	// Tru if the space queried has no items in it
	bool bHasSpace{false};
	
	// Valid if there is a single item we can swap with
	TWeakObjectPtr<UInv_InventoryItem> ValidItem{nullptr};
	
	// Upper left index of the valid item, if there is one.
	int32 ValidItemUpperLeftIndex{INDEX_NONE};	
};