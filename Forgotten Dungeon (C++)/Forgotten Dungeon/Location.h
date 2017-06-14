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
	Location(string bmpFile, string obstacleFile)
	{
		int obsX1, obsY1, obsX2, obsY2;

		BMP = al_load_bitmap(bmpFile.c_str());
		bmpXPos = 114;
		bmpYPos = 507;

		fstream File;
		File.open(obstacleFile.c_str(), ios::in);

		if (File.good())
		{
			head = new list<Obstacle *>;
			while (File >> obsX1 >> obsY1 >> obsX2 >> obsY2)
			{
				head->push_back(new Obstacle(obsX1, obsY1, obsX2, obsY2));
			}

			File.close();
		}

	}
	~Location()
	{
		while (!(head)->empty())
		{
			Obstacle* element = (head)->front();
			(head)->pop_front();
			delete element;
		}
		delete head;

		al_destroy_bitmap(BMP);
	}

	void DrawCurrentLocation()
	{
		al_draw_bitmap_region(this->BMP, bmpXPos, bmpYPos, 720, 480, 0, 0, 0);
	}

	int GetXPos() { return bmpXPos; }
	int GetYPos() { return bmpYPos; }
	void SetXPos(int XPosChange) { bmpXPos += XPosChange; }
	void SetYPos(int YPosChange) { bmpYPos += YPosChange; }
	void EscapeToStartPoint() { bmpXPos = 114; bmpYPos = 507; }

	list<Obstacle *> * GetListHead() { return head; }
	ALLEGRO_BITMAP * GetCurrentLocationBMP() { return BMP; }
};