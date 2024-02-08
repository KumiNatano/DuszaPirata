

#pragma once

#include "CoreMinimal.h"
#include "Item.h"

/**
 * 
 */
class DUSZAPIRATA_API Weapon : public UItem
{
public:
	Weapon();
	~Weapon();

	void UseItem() override;

	void ThrowItem() override;
};
