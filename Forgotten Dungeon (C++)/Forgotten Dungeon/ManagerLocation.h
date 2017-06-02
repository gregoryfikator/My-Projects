#pragma once
#include "Location.h"
#include "Manager.h"
#include "QuadTree.h"

class ManagerLocation : public Manager
{
	Location *currentLocation;
	QuadTree *rootQuadTree;

public:
	ManagerLocation() : Manager()
	{
		currentLocation = nullptr;
		rootQuadTree = nullptr;
	}
	virtual void Init(string bmpFile, string obstacleFile) // a moze konstruktor??
	{
		currentLocation = new Location(bmpFile, obstacleFile);
		rootQuadTree = new QuadTree(1);

		rootQuadTree->AssignObstaclesToSectors(currentLocation->GetListHead());
	}
	~ManagerLocation()
	{
		delete rootQuadTree->I->I;
		delete rootQuadTree->I->II;
		delete rootQuadTree->I->III;
		delete rootQuadTree->I->IV;

		delete rootQuadTree->II->I;
		delete rootQuadTree->II->II;
		delete rootQuadTree->II->III;
		delete rootQuadTree->II->IV;

		delete rootQuadTree->III->I;
		delete rootQuadTree->III->II;
		delete rootQuadTree->III->III;
		delete rootQuadTree->III->IV;

		delete rootQuadTree->IV->I;
		delete rootQuadTree->IV->II;
		delete rootQuadTree->IV->III;
		delete rootQuadTree->IV->IV;

		delete rootQuadTree->I;
		delete rootQuadTree->II;
		delete rootQuadTree->III;
		delete rootQuadTree->IV;

		//rootQuadTree->DeleteNodes(rootQuadTree);

		delete rootQuadTree;
		delete currentLocation;
	}

	int GetXPos() { return currentLocation->GetXPos(); }
	int GetYPos() { return currentLocation->GetYPos(); }
	Location *GetCurrentLocation() { return currentLocation; }
	void DrawCurrentLocation() { currentLocation->DrawCurrentLocation(); }

	bool ColisionTest(int heroX1Pos, int heroY1Pos, int heroX2Pos, int heroY2Pos, int direction)
	{
		int MapX = currentLocation->GetXPos();
		int MapY = currentLocation->GetYPos();
		int VertexLUX, VertexLUY, VertexRDX, VertexRDY;	// wspolrzedne wierzcholkow wybranego boku bitmapy bohatera (wybor boku zalezy od obranego kierunku ruchu)
		
		switch (direction)
		{
		case 1:
			VertexLUX = MapX + heroX1Pos;
			VertexLUY = MapY + heroY1Pos;
			VertexRDX = MapX + heroX2Pos;
			VertexRDY = MapY + heroY1Pos;
			break;
		case 2:
			VertexLUX = MapX + heroX1Pos;
			VertexLUY = MapY + heroY1Pos;
			VertexRDX = MapX + heroX1Pos;
			VertexRDY = MapY + heroY2Pos;
			break;
		case 3:
			VertexLUX = MapX + heroX1Pos;
			VertexLUY = MapY + heroY1Pos;
			VertexRDX = MapX + heroX2Pos;
			VertexRDY = MapY + heroY2Pos;
			break;
		case 4:
			VertexLUX = MapX + heroX1Pos;
			VertexLUY = MapY + heroY1Pos;
			VertexRDX = MapX + heroX2Pos;
			VertexRDY = MapY + heroY2Pos;
			break;
		default:
			return false;
		}

		list<Obstacle *> *list1 = rootQuadTree->GetListHead(VertexLUX, VertexLUY);
		list<Obstacle *> *list2 = rootQuadTree->GetListHead(VertexRDX, VertexRDY);

		switch (direction)	// symulacja przemieszczenia w wybranym kierunku w celu sprawdzenia kolizji
		{
		case 1:
			VertexLUY -= 3;
			VertexRDY -= 3;
			break;
		case 2:
			VertexLUX -= 3;
			VertexRDX -= 3;
			break;
		case 3:
			VertexLUY += 3;
			VertexRDY += 3;
			break;
		case 4:
			VertexLUX += 3;
			VertexRDX += 3;
			break;
		default:
			return false;
		}

		list<Obstacle *>::iterator it1 = list1->begin();
		list<Obstacle *>::iterator it2 = list2->begin();

		if (!list1->empty() && !list2->empty())
		{
			if ((*it1) != (*it2))
			{
				for (it2 = list2->begin(); it2 != list2->end(); ++it2)
					if ((VertexLUX + 32 > (*it2)->GetX1Pos()) && (VertexLUX < (*it2)->GetX2Pos()) && (VertexLUY + 32 > (*it2)->GetY1Pos()) && (VertexLUY < (*it2)->GetY2Pos()))
						return true;
			}

			for (it1 = list1->begin(); it1 != list1->end(); ++it1)
			{
				if ((VertexLUX + 32 >(*it1)->GetX1Pos()) && (VertexLUX < (*it1)->GetX2Pos()) && (VertexLUY + 32 > (*it1)->GetY1Pos()) && (VertexLUY < (*it1)->GetY2Pos()))
					return true;
			}
		}
		else
		{
			if (!list1->empty())
			{
				for (it1 = list1->begin(); it1 != list1->end(); ++it1)
					if ((VertexLUX + 32 > (*it1)->GetX1Pos()) && (VertexLUX < (*it1)->GetX2Pos()) && (VertexLUY + 32 > (*it1)->GetY1Pos()) && (VertexLUY < (*it1)->GetY2Pos()))
						return true;
			}
			else if (!list2->empty())
			{
				for (it2 = list2->begin(); it2 != list2->end(); ++it2)
					if ((VertexLUX + 32 > (*it2)->GetX1Pos()) && (VertexLUX < (*it2)->GetX2Pos()) && (VertexLUY + 32 > (*it2)->GetY1Pos()) && (VertexLUY < (*it2)->GetY2Pos()))
						return true;
			}
		}
		return false;
	}
};