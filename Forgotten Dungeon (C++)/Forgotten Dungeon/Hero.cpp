#include "Hero.h"

Hero::Hero(string newName, bool newHeroClass, string newBMP, int startPointX, int startPointY, ALLEGRO_BITMAP *newHeroPortrait, bool loadGame) : Character(newName, newBMP, startPointX, startPointY)
{
	for (int i = 0; i < 20; i++)
		eq[i] = nullptr;
	for (int i = 0; i < 6; i++)
	{
		eqDock[i] = nullptr;
		eqWorn[i] = nullptr;
	}
	eqWorn[6] = nullptr;

	heroClass = newHeroClass;
	heroPortrait = newHeroPortrait;

	heroAnimation[0] = al_create_sub_bitmap(GetBMP(), 0, 0, 32, 32);
	heroAnimation[1] = al_create_sub_bitmap(GetBMP(), 32, 0, 32, 32);
	heroAnimation[2] = al_create_sub_bitmap(GetBMP(), 64, 0, 32, 32);

	heroAnimation[3] = al_create_sub_bitmap(GetBMP(), 0, 32, 32, 32);
	heroAnimation[4] = al_create_sub_bitmap(GetBMP(), 32, 32, 32, 32);
	heroAnimation[5] = al_create_sub_bitmap(GetBMP(), 64, 32, 32, 32);

	heroAnimation[6] = al_create_sub_bitmap(GetBMP(), 0, 64, 32, 32);
	heroAnimation[7] = al_create_sub_bitmap(GetBMP(), 32, 64, 32, 32);
	heroAnimation[8] = al_create_sub_bitmap(GetBMP(), 64, 64, 32, 32);

	heroAnimation[9] = al_create_sub_bitmap(GetBMP(), 0, 96, 32, 32);
	heroAnimation[10] = al_create_sub_bitmap(GetBMP(), 32, 96, 32, 32);
	heroAnimation[11] = al_create_sub_bitmap(GetBMP(), 64, 96, 32, 32);

	if (heroClass)
		heroStats = new StatsHero(50, 25, 0, 2, 0, 30, 30, 25, 25, 25, 25, 0, heroClass);
	else
		heroStats = new StatsHero(30, 50, 0, 2, 0, 25, 25, 25, 30, 35, 30, 0, heroClass);
}

Hero::~Hero()
{
	delete heroStats;
	for (int i = 0; i < 20; i++)
		if (eq[i] != nullptr)
			delete eq[i];

	for (int i = 0; i < 7; i++)
		if (eqWorn[i] != nullptr)
			delete eqWorn[i];

	for (int i = 0; i < 12; i++)
		al_destroy_bitmap(heroAnimation[i]);
}

ALLEGRO_BITMAP * Hero::getPortrait()
{
	return heroPortrait;
}

ALLEGRO_BITMAP * Hero::getHeroAnimationFrame(int index)
{
	return heroAnimation[index];
}

bool Hero::AssignNewItem(Item *newItem)
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

Item * Hero::GetItemFromBackpack(int index)
{
	if (index >= 0 && index < 20)
		return eq[index];
	return nullptr;
}

Item * Hero::GetItemFromEquipment(int index)
{
	if (index >= 0 && index < 7)
		return eqWorn[index];
	return nullptr;
}

Skill * Hero::GetDockedSkill(int index)
{
	if (index >= 0 && index < 7)
		return eqDock[index];
	return nullptr;
}

void Hero::SwapItems(Item *&Swap1, Item *&Swap2, int indexTo, int indexFrom)
{
	Item*tmp = Swap2;
	eq[indexTo] = Swap1;
	eq[indexFrom] = tmp;
}
void Hero::SwapItems2(Item *&Swap1, Item *&Swap2, int indexTo, int indexFrom) //funkcja dla przenoszenia pierscieni pomiedzy lewa a prawa reka
{
	Item*tmp = Swap2;
	eqWorn[indexTo] = Swap1;
	eqWorn[indexFrom] = tmp;
}
void Hero::SwapItems(Item *&Swap1, Item *&Swap2, int indexTo, int indexFrom, bool ToWear)
{
	Item*tmp = Swap2;
	if (ToWear)
	{
		eqWorn[indexTo] = Swap1;
		eq[indexFrom] = tmp;
	}
	else
	{
		eq[indexTo] = Swap1;
		eqWorn[indexFrom] = tmp;
	}
}


void Hero::SwapWithEmpty(Item *&toSwap, int indexTo, int indexFrom)
{
	eq[indexTo] = toSwap;
	eq[indexFrom] = nullptr;
	eq[indexTo]->selected = false;
}

void Hero::SwapWithEmpty(Item *&toSwap, int indexTo, int indexFrom, bool wearing)
{
	if (wearing)
	{
		eqWorn[indexTo] = toSwap;
		eq[indexFrom] = nullptr;
		eqWorn[indexTo]->selected = false;
	}
	else
	{
		eq[indexTo] = toSwap;
		eqWorn[indexFrom] = nullptr;
		eq[indexTo]->selected = false;
	}
}