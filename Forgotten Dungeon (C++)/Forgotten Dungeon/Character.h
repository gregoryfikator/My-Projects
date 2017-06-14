#pragma once
#include <allegro5\allegro.h>

using namespace std;

class Character
{
	string name;
	int		lvl;

	int		X1;
	int		Y1;
	int		X2;
	int		Y2;

	ALLEGRO_BITMAP		*BMP;	// to be sprite
	int		bmpX;
	int		bmpY;
	bool	alive;

public:
	Character(string newName, string newBMP, int newX1, int newY1, int newLvl = 1)
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
	virtual ~Character()
	{
		//al_destroy_bitmap(BMP);
		////delete stats;
	}

	void SetCharacterStartPoint(int newX1, int newY1)
	{
		X1 = newX1;
		X2 = X1 + 32;

		Y1 = newY1;
		Y2 = Y1 + 32;
	}

	int GetX1Pos() { return X1; }
	int GetY1Pos() { return Y1; }
	int GetX2Pos() { return X2; }
	int GetY2Pos() { return Y2; }
	void SetXPos(int XPosChange) { X1 += XPosChange; X2 += XPosChange; }
	void SetYPos(int YPosChange) { Y1 += YPosChange; Y2 += YPosChange; }

	string GetName() { return name; }
	int GetLevel() { return lvl; }
	void IncreaseLevel() { lvl++; }
	bool CheckIfAlive() { return alive; }
	void Kill() { alive = false; }
	void Respawn() { alive = true; }

	ALLEGRO_BITMAP *GetBMP() { return BMP; }

	void DrawCharacter()
	{
		al_draw_bitmap_region(this->BMP, 0, 0, 32, 32, X1, Y1, 0);
	}
	//virtual ALLEGRO_BITMAP* getPortrait() {};
};