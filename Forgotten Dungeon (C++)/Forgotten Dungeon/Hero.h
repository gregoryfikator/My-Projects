#pragma once
#include "Character.h"
#include "Item.h"
#include "Skill.h"
#include <fstream>

class Hero :public Character
{
	ALLEGRO_BITMAP *heroPortrait;
	bool heroClass;

	StatsHero *heroStats;

	Item *eq[20];
	Item *eqWorn[7];
	Skill *eqDock[6];

	
public:
	Hero(string newName, bool newHeroClass, string newBMP, int startPointX, int startPointY, ALLEGRO_BITMAP *newHeroPortrait, bool loadGame) : Character(newName, newBMP, startPointX, startPointY)
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

		//if(loadGame)
		//{
		//	string name; // char * nazwa;
		//	vector <string>* description; // char *description[10];
		//	short int descriptionLines;
		//	short int descritptionFrameX; // int frame_x;
		//	short int descriptionFrameY; // int frame_y;

		//	short int ID;
		//	short int flag;	// mo¿e byæ nie potrzebne dziêki u¿yciu RTTI
		//	short int rarity;
		//	short int lvl;

		//	string pathFile = "saves//" + GetName() + ".sav";

		//	float dmg_min;
		//	float dmg_max;

		//	unsigned int def;

		//	float hp;	// punkty zdrowia
		//	float emp;	// punkty energii lub many w zale¿noœci od klasy postaci

		//	int str;
		//	int dur;
		//	int dex;
		//	int agi;
		//	int wis;
		//	int chr;

		//	//bmp = al_load_bitmap(bmpFile.c_str());
		//	description = new vector<string>;
		//	fstream File;
		//	//stringstream ss;

		//	File.open(pathFile.c_str(), ios::in);

		//	if (File.good())
		//	{
		//		itemList = new list<Item *>;
		//		while (File >> flag >> ID >> lvl >> rarity >> hp >> emp >> str >> dur >> dex >> agi >> wis >> chr >> dmg_min >> dmg_max >> def >> descritptionFrameX >> descriptionLines)
		//		{
		//			string tmp;

		//			descriptionFrameY = 32 + 16 * descriptionLines;

		//			getline(File, tmp);
		//			getline(File, name);

		//			for (int i = 0; i < descriptionLines; i++)
		//			{
		//				getline(File, tmp);
		//				description->push_back(tmp);
		//			}
		//			ss << ID;
		//			tmp = ss.str();
		//			bmpPath = "data//item//bmp//" + tmp + ".png";
		//			ss.str("");

		//			
		//			description = new vector<string>;
		//		}
		//		File.close();
		//	}



		//}
		//else
		//{
			if (heroClass)
			{
				heroStats = new StatsHero(50, 25, 0, 2, 0, 30, 30, 25, 25, 25, 25, heroClass);
			}
			else
			{
				heroStats = new StatsHero(30, 50, 0, 2, 0, 25, 25, 25, 30, 35, 30, heroClass);
			}
		//}

	}
	virtual ~Hero()
	{
		delete heroStats;
		for (int i = 0; i < 20; i++)
			if (eq[i] != nullptr)
				delete eq[i];

		for(int i = 0; i < 7; i++)
			if(eqWorn[i] != nullptr)
				delete eqWorn[i];
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

	Item * GetItemFromBackpack(int index)
	{
		if(index >= 0 && index < 20)
			return eq[index];
		return nullptr;
	}

	Item * GetItemFromEquipment(int index)
	{
		if (index >= 0 && index < 7)
			return eqWorn[index];
		return nullptr;
	}

	void SwapItems(Item *&Swap1, Item *&Swap2, int indexTo, int indexFrom)
	{
		Item*tmp = Swap2;
		eq[indexTo] = Swap1;
		eq[indexFrom] = tmp;
	}
	void SwapItems2(Item *&Swap1, Item *&Swap2, int indexTo, int indexFrom) //funkcja dla przenoszenia pierscieni pomiedzy lewa a prawa reka
	{
		Item*tmp = Swap2;
		eqWorn[indexTo] = Swap1;
		eqWorn[indexFrom] = tmp;
	}
	void SwapItems(Item *&Swap1, Item *&Swap2, int indexTo, int indexFrom, bool ToWear)
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
	

	void SwapWithEmpty(Item *&toSwap, int indexTo, int indexFrom)
	{
		eq[indexTo] = toSwap;
		eq[indexFrom] = nullptr;
		eq[indexTo]->selected = false;
	}

	void SwapWithEmpty(Item *&toSwap, int indexTo, int indexFrom, bool wearing)
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

	friend class ManagerItem;
	friend class ManagerSkill;
};