#pragma once
#include "Character.h"
#include "Item.h"
#include "Skill.h"

class Hero :public Character
{
	ALLEGRO_BITMAP *heroAnimation[12];
	ALLEGRO_BITMAP *heroPortrait;
	bool heroClass;
	
	Item *eq[20];
	Item *eqWorn[7];
	Skill *eqDock[6];
	
public:
	StatsHero *heroStats;

	Hero(string newName, bool newHeroClass, string newBMP, int startPointX, int startPointY, ALLEGRO_BITMAP *newHeroPortrait, bool loadGame);
	virtual ~Hero();

	ALLEGRO_BITMAP*		getPortrait();
	ALLEGRO_BITMAP*		getHeroAnimationFrame(int index);

	bool	AssignNewItem(Item *newItem);
	Item*	GetItemFromBackpack(int index);
	Item*	GetItemFromEquipment(int index);
	Skill*	GetDockedSkill(int index);
	void	SwapItems(Item *&Swap1, Item *&Swap2, int indexTo, int indexFrom);
	void	SwapItems2(Item *&Swap1, Item *&Swap2, int indexTo, int indexFrom); //funkcja dla przenoszenia pierscieni pomiedzy lewa a prawa reka
	void	SwapItems(Item *&Swap1, Item *&Swap2, int indexTo, int indexFrom, bool ToWear);
	void	SwapWithEmpty(Item *&toSwap, int indexTo, int indexFrom);
	void	SwapWithEmpty(Item *&toSwap, int indexTo, int indexFrom, bool wearing);

	friend class ManagerItem;
	friend class ManagerSkill;
};