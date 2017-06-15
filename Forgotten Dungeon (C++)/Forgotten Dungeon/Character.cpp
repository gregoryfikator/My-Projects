#include "Character.h"

Character::Character(string newName, string newBMP, int newX1, int newY1, int newLvl)
{
	name = newName;
	lvl = newLvl;

	BMP = al_load_bitmap(newBMP.c_str());
	bmpX = al_get_bitmap_width(BMP);
	bmpY = al_get_bitmap_height(BMP);

	X1 = newX1;
	X2 = X1 + 32;

	Y1 = newY1;
	Y2 = Y1 + 32;
	alive = true;
}

Character::~Character() {}

void Character::SetCharacterStartPoint(int newX1, int newY1)
{
	X1 = newX1;
	X2 = X1 + 32;

	Y1 = newY1;
	Y2 = Y1 + 32;
}

int Character::GetX1Pos() { return X1; }
int Character::GetY1Pos() { return Y1; }
int Character::GetX2Pos() { return X2; }
int Character::GetY2Pos() { return Y2; }
void Character::SetXPos(int XPosChange) { X1 += XPosChange; X2 += XPosChange; }
void Character::SetYPos(int YPosChange) { Y1 += YPosChange; Y2 += YPosChange; }

string Character::GetName() { return name; }
int Character::GetLevel() { return lvl; }
void Character::IncreaseLevel() { lvl++; }
bool Character::CheckIfAlive() { return alive; }
void Character::Kill() { alive = false; }
void Character::Respawn() { alive = true; }

ALLEGRO_BITMAP* Character::GetBMP() { return BMP; }

void Character::DrawCharacter()
{
	al_draw_bitmap_region(this->BMP, 0, 0, 32, 32, X1, Y1, 0);
}