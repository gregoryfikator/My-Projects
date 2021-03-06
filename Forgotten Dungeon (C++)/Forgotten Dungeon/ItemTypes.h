#pragma once
#include "Item.h"

class Weapon : public Item
{

public:
	Weapon(short int flag_, short int ID_, short int lvl_, short int rarity_, float hp_, float emp_, int str_, int dur_, int dex_, int agi_, int wis_, int chr_, float dmg_min_, float dmg_max_, unsigned int def_, short int descritptionFrameX_, short int descriptionFrameY_, short int descriptionLines_, string bmpPath_, string name_, vector <string>* description_) : Item(flag_, ID_, lvl_, rarity_, hp_, emp_, str_, dur_, dex_, agi_, wis_, chr_, dmg_min_, dmg_max_, def_, descritptionFrameX_, descriptionFrameY_, descriptionLines_, bmpPath_, name_, description_)
	{

	}
	Weapon(Weapon &copiedItem): Item(copiedItem)	//konstruktor kopiuj�cy, wykorzystywany w momencie zdobywania nowego przedmiotu
	{
	
	}
	virtual ~Weapon(){}

	virtual void DrawDescription() {}
};

class Shield : public Item
{

public:
	Shield(short int flag_, short int ID_, short int lvl_, short int rarity_, float hp_, float emp_, int str_, int dur_, int dex_, int agi_, int wis_, int chr_, float dmg_min_, float dmg_max_, unsigned int def_, short int descritptionFrameX_, short int descriptionFrameY_, short int descriptionLines_, string bmpPath_, string name_, vector <string>* description_) : Item(flag_, ID_, lvl_, rarity_, hp_, emp_, str_, dur_, dex_, agi_, wis_, chr_, dmg_min_, dmg_max_, def_, descritptionFrameX_, descriptionFrameY_, descriptionLines_, bmpPath_, name_, description_)
	{

	}
	Shield(Shield &copiedItem) : Item(copiedItem)	//konstruktor kopiuj�cy, wykorzystywany w momencie zdobywania nowego przedmiotu
	{

	}
	virtual ~Shield() {}
	virtual void DrawDescription() {};
};

class Helmet : public Item
{

public:
	Helmet(short int flag_, short int ID_, short int lvl_, short int rarity_, float hp_, float emp_, int str_, int dur_, int dex_, int agi_, int wis_, int chr_, float dmg_min_, float dmg_max_, unsigned int def_, short int descritptionFrameX_, short int descriptionFrameY_, short int descriptionLines_, string bmpPath_, string name_, vector <string>* description_) : Item(flag_, ID_, lvl_, rarity_, hp_, emp_, str_, dur_, dex_, agi_, wis_, chr_, dmg_min_, dmg_max_, def_, descritptionFrameX_, descriptionFrameY_, descriptionLines_, bmpPath_, name_, description_)
	{

	}
	Helmet(Helmet &copiedItem) : Item(copiedItem)	//konstruktor kopiuj�cy, wykorzystywany w momencie zdobywania nowego przedmiotu
	{

	}
	virtual ~Helmet() {}
	virtual void DrawDescription() {};
};

class ChestArmour : public Item
{

public:
	ChestArmour(short int flag_, short int ID_, short int lvl_, short int rarity_, float hp_, float emp_, int str_, int dur_, int dex_, int agi_, int wis_, int chr_, float dmg_min_, float dmg_max_, unsigned int def_, short int descritptionFrameX_, short int descriptionFrameY_, short int descriptionLines_, string bmpPath_, string name_, vector <string>* description_) : Item(flag_, ID_, lvl_, rarity_, hp_, emp_, str_, dur_, dex_, agi_, wis_, chr_, dmg_min_, dmg_max_, def_, descritptionFrameX_, descriptionFrameY_, descriptionLines_, bmpPath_, name_, description_)
	{

	}
	ChestArmour(ChestArmour &copiedItem) : Item(copiedItem)	//konstruktor kopiuj�cy, wykorzystywany w momencie zdobywania nowego przedmiotu
	{

	}
	virtual ~ChestArmour() {}
	virtual void DrawDescription() {};
};

class LegsArmour : public Item
{

public:
	LegsArmour(short int flag_, short int ID_, short int lvl_, short int rarity_, float hp_, float emp_, int str_, int dur_, int dex_, int agi_, int wis_, int chr_, float dmg_min_, float dmg_max_, unsigned int def_, short int descritptionFrameX_, short int descriptionFrameY_, short int descriptionLines_, string bmpPath_, string name_, vector <string>* description_) : Item(flag_, ID_, lvl_, rarity_, hp_, emp_, str_, dur_, dex_, agi_, wis_, chr_, dmg_min_, dmg_max_, def_, descritptionFrameX_, descriptionFrameY_, descriptionLines_, bmpPath_, name_, description_)
	{

	}
	LegsArmour(LegsArmour &copiedItem) : Item(copiedItem)	//konstruktor kopiuj�cy, wykorzystywany w momencie zdobywania nowego przedmiotu
	{

	}
	virtual ~LegsArmour() {}
	virtual void DrawDescription() {};
};

class Ring : public Item
{

public:
	Ring(short int flag_, short int ID_, short int lvl_, short int rarity_, float hp_, float emp_, int str_, int dur_, int dex_, int agi_, int wis_, int chr_, float dmg_min_, float dmg_max_, unsigned int def_, short int descritptionFrameX_, short int descriptionFrameY_, short int descriptionLines_, string bmpPath_, string name_, vector <string>* description_) : Item(flag_, ID_, lvl_, rarity_, hp_, emp_, str_, dur_, dex_, agi_, wis_, chr_, dmg_min_, dmg_max_, def_, descritptionFrameX_, descriptionFrameY_, descriptionLines_, bmpPath_, name_, description_)
	{

	}
	Ring(Ring &copiedItem) : Item(copiedItem)	//konstruktor kopiuj�cy, wykorzystywany w momencie zdobywania nowego przedmiotu
	{

	}
	virtual ~Ring() {}
	virtual void DrawDescription() {};
};