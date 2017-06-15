#pragma once
#include <allegro5/allegro_primitives.h>
#include <vector>
#include <fstream>
#include <sstream>
#include "Skill.h"
#include "Manager.h"
#include "Hero.h"
#include "Resources.h"
#include "ALLEGRO_Font.h"

using namespace std;

class ManagerSkill : public Manager
{
	vector<Skill *> *skillList;
	ALLEGRO_BITMAP *bmpMain;
	Skill * selectedSkill;
	int overlayedSkillIndex;
	int selectedSkillIndex;
	bool selectedFromTab;
	bool overlayDock;

	enum PositionToDrawDescription
	{
		NONE, RIGHT, MIDDLE, LEFT
	} position;

public:
	ManagerSkill();
	~ManagerSkill();

	virtual void Init(string itemFile = "data//skill//skilllist.txt");

	void Draw(Resources *resources, ALLEGRO_Font *allegro_font);

	Skill *GetSkill();

	int GetDescriptionDrawPosition();

	void DrawDescription(int mouseX, int mouseY, Hero *hero, Skill *skill, ALLEGRO_Font *fonts, int y = 34);

	void DrawDockedSkills(int MouseX, int MouseY, Hero *hero, ALLEGRO_Font *fonts, bool openEquipment, bool openSkillTab);

	void DrawSelectedSkill(int MouseX, int MouseY, Hero *hero);

	void AquireSkill(Hero *hero);

	void ProceedSelection(Hero *hero, int slot, bool LMBPressed, bool ToDock);

	void CheckCursorOverlayDockAndClick(int mouseX, int mouseY, Hero *hero, bool LMBPressed, bool SkillTabOpen); // funkcja jest 'nieelegancko' wykonana ze wzgledu na ograniczenia czasowe
	
	void CheckCursorOverlayTabAndClick(int mouseX, int mouseY, Hero *hero, bool LMBPressed); // funkcja jest 'nieelegancko' wykonana ze wzgledu na ograniczenia czasowe

	bool CheckButtons(int mouseX, int mouseY, Hero *hero, bool LMBPressed);

	void ResetSkillTab();

	void DropPotions();
};