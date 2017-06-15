#pragma once
#include <list>
#include <iterator>
#include "Obstacle.h"

using namespace std;

class QuadTree
{
	QuadTree * I;
	QuadTree * II;
	QuadTree * III;
	QuadTree * IV;

	list<Obstacle *> *head;

	static void GenerateQuadTree(QuadTree *pom, int Floor);

public:
	QuadTree();
	QuadTree(int Floor);
	~QuadTree();

	void AssignObstaclesToSectors(list<Obstacle *> *pom);

	list<Obstacle *> *GetListHead(int X, int Y);

	friend class ManagerLocation;
};