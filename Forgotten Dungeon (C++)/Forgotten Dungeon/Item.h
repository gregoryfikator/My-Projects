#pragma once
#include <allegro5\allegro.h>
#include <vector>
#include "Stats.h"

using namespace std;
// ta klasa musi byæ polimorficzna ¿eby dzia³a³o RTTI
class Item
{
	string name; // char * nazwa;
	vector <string> *description; // char *description[10];
	short int descriptionLines; 
	short int descritptionFrameX; // int frame_x;
	short int descriptionFrameY; // int frame_y;

	short int ID;
	short int flag;	// mo¿e byæ nie potrzebne dziêki u¿yciu RTTI
	short int rarity;
	short int lvl;

	Stats *stats; //struct Stats_EQ_MON *st;
	ALLEGRO_BITMAP *bmp;

	bool selected;

	//struct Items *next;

public:
	Item(short int flag_, short int ID_, short int lvl_, short int rarity_, float hp_, float emp_, int str_, int dur_, int dex_, int agi_, int wis_, int chr_, float dmg_min_, float dmg_max_, unsigned int def_, short int descritptionFrameX_, short int descriptionFrameY_, short int descriptionLines_, string bmpPath_, string name_, vector <string>* description_)
	{
		flag = flag_;
		ID = ID_;
		lvl = lvl_;
		rarity = rarity_;
		name = name_;

		descriptionLines = descriptionLines_;
		descritptionFrameX = descritptionFrameX_;
		descriptionFrameY = descriptionFrameY_;
		description = description_;

		bmp = al_load_bitmap(bmpPath_.c_str());

		selected = false;

		stats = new Stats(hp_, emp_, dmg_min_, dmg_max_, def_, str_, dur_, dex_, agi_, wis_, chr_);
	}

	Item(Item &copiedItem)	//konstruktor kopiuj¹cy, wykorzystywany w momencie zdobywania nowego przedmiotu
	{
		flag = copiedItem.flag;
		ID = copiedItem.ID;
		lvl = copiedItem.lvl;
		rarity = copiedItem.rarity;
		name = copiedItem.name;

		descriptionLines = copiedItem.descriptionLines;
		descritptionFrameX = copiedItem.descritptionFrameX;
		descriptionFrameY = copiedItem.descriptionFrameY;
		description = copiedItem.description;

		bmp = copiedItem.bmp;

		selected = copiedItem.selected;

		stats = copiedItem.stats;	//statystyki jednakowe dla wszystkich przedmiotow tego samego rodzaju
	}
	// void ShowItemDescription()
	// Stats *getStats() { return stats; }

	friend class Hero;
};