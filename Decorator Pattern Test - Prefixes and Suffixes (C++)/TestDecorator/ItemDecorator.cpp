#include "ItemDecorator.h"

ItemDecorator::ItemDecorator(ItemAbstract * newItem)
{
	_item = newItem;
}

ItemDecorator::~ItemDecorator()
{
	delete _item;
}
