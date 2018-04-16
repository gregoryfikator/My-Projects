#pragma once
#include <string>
#include "ItemAbstract.h"

using namespace std;

class Item : public ItemAbstract
{
	string name;

public:
	Item(string newName);
	~Item();

	string getName() { return name; };
};
