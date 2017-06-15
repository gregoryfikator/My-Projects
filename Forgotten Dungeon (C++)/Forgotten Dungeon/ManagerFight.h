#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Manager.h"
#include "Hero.h"
#include "Enemy.h"
#include <list>
#include "Allegro_Font.h"
#include "Resources.h"
#include <sstream>
#include <math.h>

class ManagerFight : public Manager
{
	Hero *hero;
	Enemy *enemy;

	list<string> *fightLog;

	double heroHR;
	double enemyHR;

	double heroHP;
	double heroEMP;
	double enemyHP;

	int round;
	bool fightFinished;
	bool escaped;

	int MouseX, MouseY;
	int DrawTextPosY;

	int usedSkill;
	int bleedingDuration;

public:
	ManagerFight();
	~ManagerFight();

	void Init(Hero *hero_, Enemy *enemy_);

	void EndFight();

	void HitRatio();

	void CompareIndicator(double HRIndicator, double *calculatedHR);

	bool Fight();

	void SetUsedSkill(int index);
	bool GetFightStatus();
	bool CheckIfHeroEscaped();
	void ResetHeroEscaped();

	void DecrementCooldowns();

	void Draw(Resources *resources, ALLEGRO_Font *allegro_font);

};