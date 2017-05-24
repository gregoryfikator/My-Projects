#pragma once
#include "Item.h"

/*
dodac wewnatrz klas jakies w³aœciwoœci typowe dla danej klasy przedmiotu (?)
*/

class Weapon : public Item
{

public:
	Weapon(short int flag_, short int ID_, short int lvl_, short int rarity_, float hp_, float emp_, int str_, int dur_, int dex_, int agi_, int wis_, int chr_, float dmg_min_, float dmg_max_, unsigned int def_, short int descritptionFrameX_, short int descriptionFrameY_, short int descriptionLines_, string bmpPath_, string name_, vector <string>* description_) : Item(flag_, ID_, lvl_, rarity_, hp_, emp_, str_, dur_, dex_, agi_, wis_, chr_, dmg_min_, dmg_max_, def_, descritptionFrameX_, descriptionFrameY_, descriptionLines_, bmpPath_, name_, description_)
	{

	}
};

class Shield : public Item
{

public:
	Shield(short int flag_, short int ID_, short int lvl_, short int rarity_, float hp_, float emp_, int str_, int dur_, int dex_, int agi_, int wis_, int chr_, float dmg_min_, float dmg_max_, unsigned int def_, short int descritptionFrameX_, short int descriptionFrameY_, short int descriptionLines_, string bmpPath_, string name_, vector <string>* description_) : Item(flag_, ID_, lvl_, rarity_, hp_, emp_, str_, dur_, dex_, agi_, wis_, chr_, dmg_min_, dmg_max_, def_, descritptionFrameX_, descriptionFrameY_, descriptionLines_, bmpPath_, name_, description_)
	{

	}
};

class Helmet : public Item
{

public:
	Helmet(short int flag_, short int ID_, short int lvl_, short int rarity_, float hp_, float emp_, int str_, int dur_, int dex_, int agi_, int wis_, int chr_, float dmg_min_, float dmg_max_, unsigned int def_, short int descritptionFrameX_, short int descriptionFrameY_, short int descriptionLines_, string bmpPath_, string name_, vector <string>* description_) : Item(flag_, ID_, lvl_, rarity_, hp_, emp_, str_, dur_, dex_, agi_, wis_, chr_, dmg_min_, dmg_max_, def_, descritptionFrameX_, descriptionFrameY_, descriptionLines_, bmpPath_, name_, description_)
	{

	}
};

class ChestArmour : public Item
{

public:
	ChestArmour(short int flag_, short int ID_, short int lvl_, short int rarity_, float hp_, float emp_, int str_, int dur_, int dex_, int agi_, int wis_, int chr_, float dmg_min_, float dmg_max_, unsigned int def_, short int descritptionFrameX_, short int descriptionFrameY_, short int descriptionLines_, string bmpPath_, string name_, vector <string>* description_) : Item(flag_, ID_, lvl_, rarity_, hp_, emp_, str_, dur_, dex_, agi_, wis_, chr_, dmg_min_, dmg_max_, def_, descritptionFrameX_, descriptionFrameY_, descriptionLines_, bmpPath_, name_, description_)
	{

	}
};

class LegsArmour : public Item
{

public:
	LegsArmour(short int flag_, short int ID_, short int lvl_, short int rarity_, float hp_, float emp_, int str_, int dur_, int dex_, int agi_, int wis_, int chr_, float dmg_min_, float dmg_max_, unsigned int def_, short int descritptionFrameX_, short int descriptionFrameY_, short int descriptionLines_, string bmpPath_, string name_, vector <string>* description_) : Item(flag_, ID_, lvl_, rarity_, hp_, emp_, str_, dur_, dex_, agi_, wis_, chr_, dmg_min_, dmg_max_, def_, descritptionFrameX_, descriptionFrameY_, descriptionLines_, bmpPath_, name_, description_)
	{

	}
};

class Ring : public Item
{

public:
	Ring(short int flag_, short int ID_, short int lvl_, short int rarity_, float hp_, float emp_, int str_, int dur_, int dex_, int agi_, int wis_, int chr_, float dmg_min_, float dmg_max_, unsigned int def_, short int descritptionFrameX_, short int descriptionFrameY_, short int descriptionLines_, string bmpPath_, string name_, vector <string>* description_) : Item(flag_, ID_, lvl_, rarity_, hp_, emp_, str_, dur_, dex_, agi_, wis_, chr_, dmg_min_, dmg_max_, def_, descritptionFrameX_, descriptionFrameY_, descriptionLines_, bmpPath_, name_, description_)
	{

	}
};