#pragma once
#include <allegro5\allegro.h>
#include <string>

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
	Character(string newName, string newBMP, int newX1, int newY1, int newLvl = 1);
	virtual ~Character();

	void SetCharacterStartPoint(int newX1, int newY1);

	int GetX1Pos();
	int GetY1Pos();
	int GetX2Pos();
	int GetY2Pos();
	void SetXPos(int XPosChange);
	void SetYPos(int YPosChange);

	string GetName();
	int GetLevel();
	void IncreaseLevel();
	bool CheckIfAlive();
	void Kill();
	void Respawn();

	ALLEGRO_BITMAP *GetBMP();

	void DrawCharacter();
};