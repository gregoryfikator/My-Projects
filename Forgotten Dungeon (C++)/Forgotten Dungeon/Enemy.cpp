#include "Enemy.h"

Enemy::Enemy(short int ID_, short int rarity_, float hp_, float emp_, int str_, int dur_, int dex_, int agi_, int wis_, int chr_, float dmg_min_, float dmg_max_, unsigned int def_, string bmpPath_, string name_, short int lvl_, short int newX1, short int newY1) : Character(name_, bmpPath_, newX1, newY1, lvl_)
{
	ID = ID_;
	rarity = rarity_;

	stats = new Stats(hp_, emp_, dmg_min_, dmg_max_, def_, str_, dur_, dex_, agi_, wis_, chr_);
}

Enemy::~Enemy()
{
	delete stats;
}