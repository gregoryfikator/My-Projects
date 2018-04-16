#pragma once
#include "ItemDecorator.h"
#include <time.h>

class Suffix : public ItemDecorator
{
	string suffixTable[5] = { "Gniewu", "Wojownika", "Mistrzostwa", "Zwyciestwa", "Bogactwa" };

public:
	Suffix(ItemAbstract * newItem) : ItemDecorator(newItem) {};
	~Suffix() {};

	string getName()
	{
		return ItemDecorator::getName() + " " + suffixTable[(rand() % 5)];
	}
};
