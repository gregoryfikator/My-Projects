#pragma once
#include <allegro5\allegro.h>
#include <vector>
#include "Stats.h"

using namespace std;
// ta klasa musi byæ polimorficzna ¿eby dzia³a³o RTTI
class Item
{
	string name; // char * nazwa;
	vector <string> description; // char *description[10];
	short int descriptionLines; 
	short int descriptionFrameX; // int frame_x;
	short int descriptionFrameY; // int frame_y;

	short int ID;
	short int flag;	// mo¿e byæ nie potrzebne dziêki u¿yciu RTTI
	short int rarity;
	short int lvl;

	Stats *stats; //struct Stats_EQ_MON *st;
	Item *original; //kopie obiektow posiadaja wskaznik na oryginalny obiekt w celu prostszego wykorzystania mechanizmu RTTI
	ALLEGRO_BITMAP *bmp;

	bool selected;

public:
	Item(short int flag_, short int ID_, short int lvl_, short int rarity_, float hp_, float emp_, int str_, int dur_, int dex_, int agi_, int wis_, int chr_, float dmg_min_, float dmg_max_, unsigned int def_, short int descritptionFrameX_, short int descriptionFrameY_, short int descriptionLines_, string bmpPath_, string name_, vector <string>* description_)
	{
		flag = flag_;
		ID = ID_;
		lvl = lvl_;
		rarity = rarity_;
		name = name_;

		descriptionLines = descriptionLines_;
		descriptionFrameX = descritptionFrameX_;
		descriptionFrameY = descriptionFrameY_;
		description = *description_;

		bmp = al_load_bitmap(bmpPath_.c_str());
		original = nullptr;
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
		descriptionFrameX = copiedItem.descriptionFrameX;
		descriptionFrameY = copiedItem.descriptionFrameY;
		description = copiedItem.description;

		bmp = copiedItem.bmp;
		original = &copiedItem;
		selected = copiedItem.selected;

		stats = copiedItem.stats;	//statystyki jednakowe dla wszystkich przedmiotow tego samego rodzaju
	}
	virtual void DrawDescription() {};
	// Stats *getStats() { return stats; }

	friend class Hero;
	friend class ManagerItem;
};