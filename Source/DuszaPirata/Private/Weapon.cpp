


#include "Weapon.h"

Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}

void Weapon::UseItem()
{
	UItem::UseItem();
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, TEXT("Item to bron, strzelono")); 
}

void Weapon::ThrowItem()
{
	UItem::ThrowItem();
}
