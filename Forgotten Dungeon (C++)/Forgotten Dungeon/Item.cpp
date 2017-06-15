#include  "Item.h"

Item::Item(short int flag_, short int ID_, short int lvl_, short int rarity_, float hp_, float emp_, int str_, int dur_, int dex_, int agi_, int wis_, int chr_, float dmg_min_, float dmg_max_, unsigned int def_, short int descritptionFrameX_, short int descriptionFrameY_, short int descriptionLines_, string bmpPath_, string name_, vector <string>* description_)
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
	description_->clear();
	delete description_;
	bmp = al_load_bitmap(bmpPath_.c_str());
	original = nullptr;
	selected = false;

	stats = new Stats(hp_, emp_, dmg_min_, dmg_max_, def_, str_, dur_, dex_, agi_, wis_, chr_);
}

Item::Item(Item &copiedItem)	//konstruktor kopiuj¹cy, wykorzystywany w momencie zdobywania nowego przedmiotu
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

Item::~Item()
{
	if (original == nullptr)
	{
		al_destroy_bitmap(bmp);
		delete stats;
	}

	description.erase(description.begin(), description.end());
}