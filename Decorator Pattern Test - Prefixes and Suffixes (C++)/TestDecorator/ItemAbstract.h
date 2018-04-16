#pragma once
#include <string>

using namespace std;

class ItemAbstract
{
public:
	virtual ~ItemAbstract();
	virtual string getName() = 0;
};
