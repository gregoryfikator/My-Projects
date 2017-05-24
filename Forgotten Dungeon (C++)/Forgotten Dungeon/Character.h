#pragma once
#include <allegro5\allegro.h>
#include <string> 
#include "Stats.h"

using namespace std;

class Character
{
	string name;

	int		X1;
	int		Y1;
	int		X2;
	int		Y2;

	ALLEGRO_BITMAP		*BMP;	// to be sprite
	int		bmpX;
	int		bmpY;

	Stats *stats;

public:
	Character(string newName, string newBMP, int newX1, int newY1)
	{
		name = newName;

		BMP = al_load_bitmap(newBMP.c_str());
		bmpX = al_get_bitmap_width(BMP);
		bmpY = al_get_bitmap_height(BMP);

		X1 = newX1;
		X2 = X1 + 32;

		Y1 = newY1;
		Y2 = Y1 + 32;
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
	Stats *GetStats() { return stats; }

	void DrawCharacter()
	{
		al_draw_bitmap_region(this->BMP, 0, 0, 32, 32, X1, Y1, 0);
	}
	//virtual ALLEGRO_BITMAP* getPortrait() {};
};