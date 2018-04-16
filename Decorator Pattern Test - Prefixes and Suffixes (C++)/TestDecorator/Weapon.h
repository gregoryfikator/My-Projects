#pragma once
#include "Item.h"

class Weapon : public Item
{
	
public:
	Weapon(string newName) : Item(newName){};
	~Weapon() {};
};
