#pragma once
#define CRT_SECURE_NO_WARNINGS

//#include <allegro5\allegro.h>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "Manager.h"
#include "ItemTypes.h"

class ManagerItem : public Manager
{
	list<Item *> *itemList;

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
			itemList = new list<Item *>;
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

	virtual void Draw(Hero *hero, Resources *resources, ALLEGRO_Font *allegro_font)
	{
		// rysowanie ekwipunku
		al_draw_filled_rectangle(0, 0, 720, 480, al_map_rgba(0, 0, 0, 175));
		al_draw_bitmap(resources->ui_eq, 30, 43, 0);
		al_draw_filled_rounded_rectangle(282, 341, 282 + 20, 362, 2, 2, al_map_rgb(45, 210, 55)); //al_draw_filled_rounded_rectangle(282, 341, 282 + x_percent_part, 362, 2, 2, al_map_rgb(45, 210, 55));
		al_draw_bitmap(resources->ui_xp_bar, 259, 305, 0);

		// efekt podswietlenia t³a przedmiotow w ekwipunku - realizowany w metodzie DrawItemsFromBackpack()

		this->DrawItemsFromBackpack(hero);

		// tutaj powinny byc rysowane efekty takie jak przyciemnienie przedmiotow w ekwipunku

		al_draw_bitmap(resources->ui_eq_list, 64, 107, 0);
		al_draw_bitmap(resources->ui_eq_wear, 258, 107, 0);

		//if (debugModeOn) // docelowo kosz staje sie aktywny i mozna usunac przedmiot gdy zostanie zaznaczony
			al_draw_bitmap(resources->ui_bin, 53, 379, 0);
	}

	static void DrawItemsFromBackpack(Hero *hero)
	{
		int slot = 0;
		int slotX = 71;
		int slotY = 113;

		for (int j = 0; j < 5; j++, slotY += 43, slotX = 71)
		{
			for (int k = 0; k < 4; k++, slot++, slotX += 43)
			{
				if (hero->eq[slot] != nullptr)
				{
					if (hero->eq[slot]->selected)
						al_draw_filled_rounded_rectangle(slotX - 2, slotY - 1, slotX + 43, slotY + 43, 8, 8, al_map_rgb(30, 255, 30));

					al_draw_scaled_bitmap(hero->eq[slot]->bmp, 0, 0, al_get_bitmap_width(hero->eq[slot]->bmp), al_get_bitmap_height(hero->eq[slot]->bmp), slotX, slotY, 42, 42, 0);
				}
			}
		}
	}

	Item DropItem() //metoda losuje przedmiot zdobywany po pokonaniu przeciwnika
	{
		int stop = rand() % itemList->size();
		int i = 0;
		for (list<Item *>::iterator it = itemList->begin() ; it != itemList->end(); it++, i++)
			if (i == stop)
				return **it;
	} 
};