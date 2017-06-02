#pragma once
#include <allegro5\allegro.h>
#include <string>
#include <vector>
#include "Stats.h"


class Skill
{
	string name; // char * nazwa;
	vector <string> description; // char *description[10];
	short int descriptionLines;
	short int descriptionFrameX; // int frame_x;
	short int descriptionFrameY; // int frame_y;

	short int ID;
	short int flag;	// mo¿e byæ nie potrzebne dziêki u¿yciu RTTI
	short int quantity; // dla mikstur
	short int cooldown;

	StatsSkill *stats; //struct Stats_EQ_MON *st;
	ALLEGRO_BITMAP *bmp;

	bool selected;

public:
	Skill(short int flag_, short int ID_, short int cooldown_, float hp_, float hpRegen_, short int hpRegenDuration_, float emp_, float empRegen_, short int empRegenDuration_, unsigned int def_, float defMultipler_, short int defMultiplerDuration_, float dmgGivenMultipler_, short int dmgGivenMultiplerDuration_, float dmgTakenMultipler_, short int dmgTakenMultiplerDuration_, float doubleStrikeChance_, short int doubleStrikeDuration_, float bleedingChance_, short int bleedingDuration_, bool unblockable_, bool fallback_, short int descritptionFrameX_, short int descriptionFrameY_, short int descriptionLines_, string bmpPath_, string name_, vector <string> *description_, short int bmpXoffset_ = 0, short int bmpYoffset_ = 0, ALLEGRO_BITMAP *mainBMP_ = nullptr, short int quantity_ = 0)
	{
		ID = ID_;
		flag = flag_;
		quantity = quantity_;
		cooldown = cooldown_;

		descriptionFrameX = descritptionFrameX_;
		descriptionFrameY = descriptionFrameY_;
		descriptionLines = descriptionLines_;

		name = name_;

		description = *description_;
		description_->clear();
		delete description_;

		if (flag == 0)
			bmp = al_load_bitmap(bmpPath_.c_str());
		else
			bmp = al_create_sub_bitmap(mainBMP_, bmpXoffset_, bmpYoffset_, 42, 42);

		selected = false;

		stats = new StatsSkill(hp_, hpRegen_, hpRegenDuration_, emp_, empRegen_, empRegenDuration_, def_, defMultipler_, defMultiplerDuration_, dmgGivenMultipler_, dmgGivenMultiplerDuration_, dmgTakenMultipler_, dmgTakenMultiplerDuration_, doubleStrikeChance_, doubleStrikeDuration_, bleedingChance_, bleedingDuration_, unblockable_, fallback_);
	}

	~Skill()
	{
		delete stats;
		description.erase(description.begin(), description.end());
		al_destroy_bitmap(bmp);
	}
	friend class ManagerSkill;
};