#include "Location.h"

Location::Location(string bmpFile, string obstacleFile)
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
Location::~Location()
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

void Location::DrawCurrentLocation()
{
	al_draw_bitmap_region(this->BMP, bmpXPos, bmpYPos, 720, 480, 0, 0, 0);
}

int Location::GetXPos() { return bmpXPos; }
int Location::GetYPos() { return bmpYPos; }
void Location::SetXPos(int XPosChange) { bmpXPos += XPosChange; }
void Location::SetYPos(int YPosChange) { bmpYPos += YPosChange; }
void Location::EscapeToStartPoint() { bmpXPos = 114; bmpYPos = 507; }

list<Obstacle *> * Location::GetListHead() { return head; }
ALLEGRO_BITMAP * Location::GetCurrentLocationBMP() { return BMP; }