#pragma once
#include "Location.h"
#include "Manager.h"
#include "QuadTree.h"
#include "Enemy.h"
#include <vector>
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
	ManagerLocation();
	virtual void Init(string bmpFile, string obstacleFile, string characterFile);
	~ManagerLocation();

	int GetXPos();
	int GetYPos();
	Location *GetCurrentLocation();
	void DrawCurrentLocation();
	void RespawnEnemy();
	void DrawSpawnedEnemies();

	bool GetFightStatus();
	void SetFightStatus(bool newStatus);
	int GetSpawnedEnemyIndex();
	Character *GetEnemy();
	void KillEnemy();

	bool ColisionTest(int heroX1Pos, int heroY1Pos, int heroX2Pos, int heroY2Pos, int direction);
};