#include "Skill.h"

Skill::Skill(short int flag_, short int ID_, short int cooldown_, float hp_, float hpRegen_, short int hpRegenDuration_, float emp_, float empRegen_, short int empRegenDuration_, unsigned int def_, float defMultipler_, short int defMultiplerDuration_, float dmgGivenMultipler_, short int dmgGivenMultiplerDuration_, float dmgTakenMultipler_, short int dmgTakenMultiplerDuration_, float doubleStrikeChance_, short int doubleStrikeDuration_, float bleedingChance_, short int bleedingDuration_, bool unblockable_, bool fallback_, short int descritptionFrameX_, short int descriptionFrameY_, short int descriptionLines_, string bmpPath_, string name_, vector <string> *description_, short int bmpXoffset_, short int bmpYoffset_, ALLEGRO_BITMAP *mainBMP_, short int quantity_)
{
	ID = ID_;
	flag = flag_;
	quantity = quantity_;
	cooldown = cooldown_;
	currentCooldown = 0;

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

Skill::~Skill()
{
	delete stats;
	description.erase(description.begin(), description.end());
	al_destroy_bitmap(bmp);
}