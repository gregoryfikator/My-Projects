#pragma once
#include <allegro5\allegro.h>
#include <vector>
#include "Stats.h"

using namespace std;

class Item
{
	string name; 
	vector <string> description; 
	short int descriptionLines; 
	short int descriptionFrameX; 
	short int descriptionFrameY; 

	short int ID;
	short int flag;	
	short int rarity;
	short int lvl;

	Stats *stats; 
	Item *original; //kopie obiektow posiadaja wskaznik na oryginalny obiekt w celu prostszego wykorzystania mechanizmu RTTI
	ALLEGRO_BITMAP *bmp;

	bool selected;

public:
	Item(short int flag_, short int ID_, short int lvl_, short int rarity_, float hp_, float emp_, int str_, int dur_, int dex_, int agi_, int wis_, int chr_, float dmg_min_, float dmg_max_, unsigned int def_, short int descritptionFrameX_, short int descriptionFrameY_, short int descriptionLines_, string bmpPath_, string name_, vector <string>* description_);
	Item(Item &copiedItem);	//konstruktor kopiuj¹cy, wykorzystywany w momencie zdobywania nowego przedmiotu

	virtual ~Item();

	virtual void DrawDescription() {};

	friend class Hero;
	friend class ManagerItem;
};