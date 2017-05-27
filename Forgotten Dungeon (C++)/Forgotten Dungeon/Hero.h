#pragma once
#include "Character.h"
#include "Item.h"
#include "Skill.h"

class Hero :public Character
{
	ALLEGRO_BITMAP *heroPortrait;
	bool heroClass;

	StatsHero *heroStats;

	Item *eq[20];
	Item *eqWorn[7];
	Skill *eqDock[7];

	
public:
	Hero(string newName, bool newHeroClass, string newBMP, int startPointX, int startPointY, ALLEGRO_BITMAP *newHeroPortrait) : Character(newName, newBMP, startPointX, startPointY)
	{
		for (int i = 0; i < 20; i++)
			eq[i] = nullptr;
		for (int i = 0; i < 7; i++)
		{
			eqDock[i] = nullptr;
			eqWorn[i] = nullptr;
		}

		heroClass = newHeroClass;
		heroPortrait = newHeroPortrait;
		heroStats = nullptr;
	}

	ALLEGRO_BITMAP * getPortrait()
	{
		return heroPortrait;
	}


	// poni¿sze metody znajd¹ siê w klasie ManagerItem
	bool AssignNewItem(Item *newItem)
	{
		for (int i = 0; i < 20; i++)
		{
			if (eq[i] == nullptr)
			{
				eq[i] = newItem;
				return true;
			}
		}		
		return false;
	}

	friend class ManagerItem;
};