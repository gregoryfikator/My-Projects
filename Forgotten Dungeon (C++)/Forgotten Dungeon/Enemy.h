#pragma once
#include "Character.h"
#include <string>
#include "Stats.h"

class Enemy: public Character
{
	int ID;
	int rarity;
	
public:
	Stats *stats;

	Enemy(short int ID_, short int rarity_, float hp_, float emp_, int str_, int dur_, int dex_, int agi_, int wis_, int chr_, float dmg_min_, float dmg_max_, unsigned int def_, string bmpPath_, string name_, short int lvl_, short int newX1, short int newY1);
	~Enemy();
};