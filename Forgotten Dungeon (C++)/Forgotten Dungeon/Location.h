#pragma once
#include <allegro5\allegro.h>
#include <string>
#include <fstream>
#include <list>
#include "Obstacle.h"

using namespace std;

class Location
{
	ALLEGRO_BITMAP *BMP;
	int bmpXPos;
	int bmpYPos;

	list<Obstacle *> *head;

public:
	Location(string bmpFile, string obstacleFile);
	~Location();

	void DrawCurrentLocation();

	int GetXPos();
	int GetYPos();
	void SetXPos(int XPosChange);
	void SetYPos(int YPosChange);
	void EscapeToStartPoint();

	list<Obstacle *> * GetListHead();
	ALLEGRO_BITMAP * GetCurrentLocationBMP();
};