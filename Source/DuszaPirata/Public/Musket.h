

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"

/**
 * 
 */
class DUSZAPIRATA_API Musket : public UWeapon
{
public:
	Musket();
	~Musket();

	
	int HowMuchAmmo;
	void UseItem() override;

	void Shoot();
};
