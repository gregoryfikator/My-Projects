#pragma once
#define CRT_SECURE_NO_WARNINGS

//#include <allegro5\allegro.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "Manager.h"
#include "ItemTypes.h"

class ManagerItem : public Manager
{
	vector<Item *> *itemList;

public:
	virtual void Init(string itemFile = "data//item//itemlist.txt")
	{

		string name; // char * nazwa;
		vector <string>* description; // char *description[10];
		short int descriptionLines; 
		short int descritptionFrameX; // int frame_x;
		short int descriptionFrameY; // int frame_y;

		short int ID;
		short int flag;	// mo¿e byæ nie potrzebne dziêki u¿yciu RTTI
		short int rarity;
		short int lvl;

		string bmpPath;

		float dmg_min;
		float dmg_max;

		unsigned int def;

		float hp;	// punkty zdrowia
		float emp;	// punkty energii lub many w zale¿noœci od klasy postaci

		int str;
		int dur;
		int dex;
		int agi;
		int wis;
		int chr;

		//bmp = al_load_bitmap(bmpFile.c_str());
		description = new vector<string>;
		fstream File;
		stringstream ss;

		File.open(itemFile.c_str(), ios::in);

		if (File.good())
		{
			itemList = new vector<Item *>;
			while (File >> flag >> ID >> lvl >> rarity >> hp >> emp >> str >> dur >> dex >> agi >> wis >> chr >> dmg_min >> dmg_max >> def >> descritptionFrameX >> descriptionLines)
			{
				string tmp;

				descriptionFrameY = 32 + 16 * descriptionLines;

				getline(File, tmp);
				getline(File, name);

				for (int i = 0; i < descriptionLines; i++)
				{
					getline(File, tmp);
					description->push_back(tmp);
				}
				ss << ID;		
				tmp = ss.str();
				bmpPath = "data//item//bmp//" + tmp + ".png";
				ss.str("");

				switch (flag)
				{
				case 1:
					itemList->push_back(new Weapon(flag, ID, lvl, rarity, hp, emp, str, dur, dex, agi, wis, chr, dmg_min, dmg_max, def, descritptionFrameX, descriptionFrameY, descriptionLines, bmpPath, name, description));
					break;
				case 2:
					itemList->push_back(new Shield(flag, ID, lvl, rarity, hp, emp, str, dur, dex, agi, wis, chr, dmg_min, dmg_max, def, descritptionFrameX, descriptionFrameY, descriptionLines, bmpPath, name, description));
					break;
				case 3:
					itemList->push_back(new Helmet(flag, ID, lvl, rarity, hp, emp, str, dur, dex, agi, wis, chr, dmg_min, dmg_max, def, descritptionFrameX, descriptionFrameY, descriptionLines, bmpPath, name, description));
					break;
				case 4:
					itemList->push_back(new ChestArmour(flag, ID, lvl, rarity, hp, emp, str, dur, dex, agi, wis, chr, dmg_min, dmg_max, def, descritptionFrameX, descriptionFrameY, descriptionLines, bmpPath, name, description));
					break;
				case 5:
					itemList->push_back(new LegsArmour(flag, ID, lvl, rarity, hp, emp, str, dur, dex, agi, wis, chr, dmg_min, dmg_max, def, descritptionFrameX, descriptionFrameY, descriptionLines, bmpPath, name, description));
					break;
				case 6:
					itemList->push_back(new Ring(flag, ID, lvl, rarity, hp, emp, str, dur, dex, agi, wis, chr, dmg_min, dmg_max, def, descritptionFrameX, descriptionFrameY, descriptionLines, bmpPath, name, description));
					break;
				default:
					break;
				}
				description = new vector<string>;
			}
			File.close();
		}

		// zaladowac z pliku itemy do listy, brac pod uwage flagi przedmiotow przy tworzeniu nowych obiektów
		// flagi moga byc nie potrzebne dziêki u¿yciu RTTI
	}
	Item DropItem() //metoda losuje przedmiot zdobywany po pokonaniu przeciwnika
	{
		int stop = rand() % itemList->size();
		int i = 0;
		for (vector<Item *>::iterator it = itemList->begin() ; it != itemList->end(); it++, i++)
			if (i == stop)
				return **it;
	} 
};