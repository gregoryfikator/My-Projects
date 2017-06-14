#pragma once
#include "Location.h"
#include "Manager.h"
#include "QuadTree.h"
#include "Enemy.h"
#include <sstream>

class ManagerLocation : public Manager
{
	Location *currentLocation;
	QuadTree *rootQuadTree;

	vector<Character *> *character;
	vector<Character *> *spawnedEnemies;

	bool fight;
	int spawnedEnemyIndex;

public:
	ManagerLocation() : Manager()
	{
		currentLocation = nullptr;
		rootQuadTree = nullptr;
		character = nullptr;
		spawnedEnemies = nullptr;

		fight = false;
		spawnedEnemyIndex = -1;
	}
	virtual void Init(string bmpFile, string obstacleFile, string characterFile) // a moze konstruktor??
	{
		currentLocation = new Location(bmpFile, obstacleFile);
		rootQuadTree = new QuadTree(1);

		rootQuadTree->AssignObstaclesToSectors(currentLocation->GetListHead());

		fstream File;
		File.open(characterFile.c_str(), ios::in);

		if (File.good())
		{
			short int ID_;
			short int rarity_;
			float hp_;
			float emp_;
			int str_;
			int dur_;
			int dex_;
			int agi_;
			int wis_;
			int chr_;
			float dmg_min_;
			float dmg_max_;
			unsigned int def_;
			string name_;
			short int lvl_;
			short int newX1;
			short int newY1;

			character = new vector<Character *>;
			spawnedEnemies = new vector<Character *>;

			while (File >> ID_ >> rarity_ >> hp_ >> emp_ >> str_ >> dur_ >> dex_ >> agi_ >> wis_ >> chr_ >> dmg_min_ >> dmg_max_ >> def_ >> lvl_ >> newX1 >> newY1)
			{
				string tmp;
				stringstream ss;

				getline(File, tmp);
				getline(File, name_);

				ss << ID_;
				tmp = ss.str();
				string bmpPath = "data//character//bmp//" + tmp + ".png";
				ss.str("");

				character->push_back(new Enemy(ID_, rarity_, hp_, emp_, str_, dur_, dex_, agi_, wis_, chr_, dmg_min_, dmg_max_, def_, bmpPath, name_, lvl_,  newX1, newY1));
				spawnedEnemies->push_back(new Enemy(ID_, rarity_, hp_, emp_, str_, dur_, dex_, agi_, wis_, chr_, dmg_min_, dmg_max_, def_, bmpPath, name_, lvl_, newX1, newY1));
			}
			File.close();
		}

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

		delete rootQuadTree;
		delete currentLocation;

		for (int i = 0; i < character->size(); i++)
		{
			Character* element = character->at(i);
			delete element;
		}
		delete character;

		for (int i = 0; i < spawnedEnemies->size(); i++)
		{
			Character* element = spawnedEnemies->at(i);
			delete element;
		}
		delete spawnedEnemies;	
	}

	int GetXPos() { return currentLocation->GetXPos(); }
	int GetYPos() { return currentLocation->GetYPos(); }
	Location *GetCurrentLocation() { return currentLocation; }
	void DrawCurrentLocation() { currentLocation->DrawCurrentLocation(); }
	void RespawnEnemy()
	{
		if (spawnedEnemyIndex == 0)
			spawnedEnemies->at(1)->Respawn();
		else if (spawnedEnemyIndex == 1)
			spawnedEnemies->at(0)->Respawn();
	}
	void DrawSpawnedEnemies()
	{
		int MapX = currentLocation->GetXPos();
		int MapY = currentLocation->GetYPos();

		for (int i = 0; i < spawnedEnemies->size(); i++)
			if (MapX + 720 >= spawnedEnemies->at(i)->GetX1Pos() && MapX <= spawnedEnemies->at(i)->GetX2Pos() && MapY + 480 >= spawnedEnemies->at(i)->GetY1Pos() && MapY <= spawnedEnemies->at(i)->GetY2Pos() && spawnedEnemies->at(i)->CheckIfAlive() == true)
				al_draw_bitmap(spawnedEnemies->at(i)->GetBMP(), spawnedEnemies->at(i)->GetX1Pos() - MapX, spawnedEnemies->at(i)->GetY1Pos() - MapY, 0);
	}

	bool GetFightStatus() { return fight; }
	void SetFightStatus(bool newStatus) { fight = newStatus; }
	int GetSpawnedEnemyIndex() { return spawnedEnemyIndex; }
	Character *GetEnemy() { return spawnedEnemies->at(spawnedEnemyIndex); }
	void KillEnemy() { this->GetEnemy()->Kill(); }

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
			//VertexRDY -= 3;
			break;
		case 2:
			VertexLUX -= 3;
			//VertexRDX -= 3;
			break;
		case 3:
			VertexLUY += 3;
			//VertexRDY += 3;
			break;
		case 4:
			VertexLUX += 3;
			//VertexRDX += 3;
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
					if ((VertexLUX + 32 > (*it2)->GetX1Pos()) && (VertexLUX < (*it2)->GetX2Pos()) && (VertexLUY + 32 >(*it2)->GetY1Pos()) && (VertexLUY < (*it2)->GetY2Pos()))
						return true;
			}

			for (it1 = list1->begin(); it1 != list1->end(); ++it1)
			{
				if ((VertexLUX + 32 > (*it1)->GetX1Pos()) && (VertexLUX < (*it1)->GetX2Pos()) && (VertexLUY + 32 >(*it1)->GetY1Pos()) && (VertexLUY < (*it1)->GetY2Pos()))
					return true;
			}
		}
		else
		{
			if (!list1->empty())
			{
				for (it1 = list1->begin(); it1 != list1->end(); ++it1)
					if ((VertexLUX + 32 > (*it1)->GetX1Pos()) && (VertexLUX < (*it1)->GetX2Pos()) && (VertexLUY + 32 >(*it1)->GetY1Pos()) && (VertexLUY < (*it1)->GetY2Pos()))
						return true;
			}
			else if (!list2->empty())
			{
				for (it2 = list2->begin(); it2 != list2->end(); ++it2)
					if ((VertexLUX + 32 > (*it2)->GetX1Pos()) && (VertexLUX < (*it2)->GetX2Pos()) && (VertexLUY + 32 >(*it2)->GetY1Pos()) && (VertexLUY < (*it2)->GetY2Pos()))
						return true;
			}
		}

		for (int i = 0; i < spawnedEnemies->size(); i++)
			if ((VertexLUX + 32 > spawnedEnemies->at(i)->GetX1Pos()) && (VertexLUX < spawnedEnemies->at(i)->GetX2Pos()) && (VertexLUY + 32 > spawnedEnemies->at(i)->GetY1Pos()) && (VertexLUY < spawnedEnemies->at(i)->GetY2Pos()) && spawnedEnemies->at(i)->CheckIfAlive() == true)
			{
				fight = true;
				spawnedEnemyIndex = i;
				return true;
			}

		fight = false;
		spawnedEnemyIndex = -1;
		return false;
	}
};