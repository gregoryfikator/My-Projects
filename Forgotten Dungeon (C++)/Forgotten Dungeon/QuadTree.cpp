#include "QuadTree.h"

void QuadTree::GenerateQuadTree(QuadTree *pom, int Floor)
{
	pom->I = new QuadTree();
	pom->II = new QuadTree();
	pom->III = new QuadTree();
	pom->IV = new QuadTree();

	if (Floor > 0)
	{
		GenerateQuadTree(pom->I, Floor - 1);
		GenerateQuadTree(pom->II, Floor - 1);
		GenerateQuadTree(pom->III, Floor - 1);
		GenerateQuadTree(pom->IV, Floor - 1);
	}
	else
	{
		pom->I->head = new list<Obstacle *>;
		pom->II->head = new list<Obstacle *>;
		pom->III->head = new list<Obstacle *>;
		pom->IV->head = new list<Obstacle *>;
	}
}

QuadTree::QuadTree()
{
	I = nullptr;
	II = nullptr;
	III = nullptr;
	IV = nullptr;

	head = nullptr;
}
QuadTree::QuadTree(int Floor)
{
	GenerateQuadTree(this, Floor);
}
QuadTree::~QuadTree()
{
	if (head != nullptr)
	{
		while (!head->empty())
		{
			Obstacle* element = head->front();
			head->pop_front();
			delete element;
		}
		delete head;
	}
}

void QuadTree::AssignObstaclesToSectors(list<Obstacle *> *pom)
{
	if (!pom->empty())
		for (list<Obstacle *>::iterator it = pom->begin(); it != pom->end(); ++it)
		{
			Obstacle * addedElement = new Obstacle(*(*it));
			list<Obstacle *> *listToUpdate = GetListHead((*it)->GetX1Pos(), (*it)->GetY1Pos());
			listToUpdate->push_back(addedElement);
		}
}

list<Obstacle *> * QuadTree::GetListHead(int X, int Y)
{
	if (X <= 750)
	{
		if (X <= 375)
		{
			if (Y <= 750)
			{
				if (Y <= 375)
					return this->I->I->head;
				else
					return this->I->II->head;
			}
			else
			{
				if (Y <= 1125)
					return this->I->III->head;
				else
					return this->I->IV->head;
			}
		}
		else
		{
			if (Y <= 750)
			{
				if (Y <= 375)
					return this->II->I->head;
				else
					return this->II->II->head;
			}
			else
			{
				if (Y <= 1125)
					return this->II->III->head;
				else
					return this->II->IV->head;
			}
		}
	}
	else
	{
		if (X <= 1125)
		{
			if (Y <= 750)
			{
				if (Y <= 375)
					return this->III->I->head;
				else
					return this->III->II->head;
			}
			else
			{
				if (Y <= 1125)
					return this->III->III->head;
				else
					return this->III->IV->head;
			}
		}
		else
		{
			if (Y <= 750)
			{
				if (Y <= 375)
					return this->IV->I->head;
				else
					return this->IV->II->head;
			}
			else
			{
				if (Y <= 1125)
					return this->IV->III->head;
				else
					return this->IV->IV->head;
			}
		}
	}
}