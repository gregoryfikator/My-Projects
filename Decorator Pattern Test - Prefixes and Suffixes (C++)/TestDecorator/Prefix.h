#pragma once
#include "ItemDecorator.h"
#include <time.h>

class Prefix : public ItemDecorator
{
	string prefixTable[5] = { "Wielki", "Znakomity", "Zardzewialy", "Stalowy", "Naostrzony" };

public:
	Prefix(ItemAbstract * newItem) : ItemDecorator(newItem) {};
	~Prefix() {};

	string getName()
	{		
		return prefixTable[(rand() % 5)] + " " + ItemDecorator::getName();
	}
};
