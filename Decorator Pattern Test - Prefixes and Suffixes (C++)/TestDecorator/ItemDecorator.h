#pragma once
#include "Item.h"

class ItemDecorator : public ItemAbstract
{
	ItemAbstract * _item;

public:
	ItemDecorator(ItemAbstract * newItem);
	~ItemDecorator();

	string getName() { return _item->getName(); };
};
