

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"

/**
 * 
 */
class DUSZAPIRATA_API Musket : public Weapon
{
public:
	Musket();
	~Musket();

	
	int HowMuchAmmo;
	void UseItem() override;

	void Shoot();
};
