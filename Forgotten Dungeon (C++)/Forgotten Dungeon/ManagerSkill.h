#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include "Skill.h"

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
	ManagerSkill() : Manager()
	{
		skillList = nullptr;
		bmpMain = al_load_bitmap("data//skill//bmp//skillTable.png");
		selectedSkill = nullptr;
		overlayedSkillIndex = -1;
		selectedSkillIndex = -1;	
		selectedFromTab = false;
		overlayDock = false;
		position = NONE;
	}
	~ManagerSkill()
	{
		for (int i = 0; i < skillList->size(); i++)
		{
			Skill* element = skillList->at(i);
			delete element;
		}
		delete skillList;

		if (bmpMain != nullptr)
			al_destroy_bitmap(bmpMain);
	}
	virtual void Init(string itemFile = "data//skill//skilllist.txt")
	{
		short int flag;	// mo¿e byæ nie potrzebne dziêki u¿yciu RTTI
		short int ID;	
		short int cooldown;

		int hp;		// efekt u¿ycia umiejêtnoœci/mikstury
		float hpRegen;
		short int hpRegenDuration;

		int emp;	// efekt u¿ycia umiejêtnoœci/mikstury
		float empRegen;
		short int empRegenDuration;

		int def;
		float defMultipler;
		short int defMultiplerDuration;

		float dmgGivenMultipler;
		short int dmgGivenMultiplerDuration;

		float dmgTakenMultipler;
		short int dmgTakenMultiplerDuration;

		float doubleStrikeChance;
		short int doubleStrikeDuration;

		float bleedingChance;
		short int bleedingDuration;

		bool unblockable;
		bool fallback;

		short int bmpXoffset;
		short int bmpYoffset;

		short int descritptionFrameX; // int frame_x;
		short int descriptionFrameY; // int frame_y;
		short int descriptionLines;
		
		string name; // char * nazwa;
		vector <string> *description = new vector<string>;

		string bmpPath;

		fstream File;
		stringstream ss;
		
		File.open(itemFile.c_str(), ios::in);

		if (File.good())
		{
			skillList = new vector<Skill *>;
			while (File >> flag >> ID >> cooldown >> hp >> hpRegen >> hpRegenDuration >> emp >> empRegen >> empRegenDuration >> def >> defMultipler >> defMultiplerDuration >> dmgGivenMultipler >> dmgGivenMultiplerDuration >> dmgTakenMultipler >> dmgTakenMultiplerDuration >> doubleStrikeChance >> doubleStrikeDuration >> bleedingChance >> bleedingDuration >> unblockable >> fallback >> bmpXoffset >> bmpYoffset >> descritptionFrameX >> descriptionLines)
			{
				string tmp;

				descriptionFrameY = 32 + 16 * descriptionLines;

				getline(File, tmp);
				getline(File, name);

				for (int i = 0; i < descriptionLines; i++)
				{
					getline(File, tmp);
					description->push_back(tmp);
				}

				if (flag == 0)
				{
					descriptionFrameY += 16;
					ss << ID;
					tmp = ss.str();
					bmpPath = "data//skill//bmp//" + tmp + ".png";
					ss.str("");

					skillList->push_back(new Skill(flag, ID, cooldown, hp, hpRegen, hpRegenDuration, emp, empRegen, empRegenDuration, def, defMultipler, defMultiplerDuration, dmgGivenMultipler, dmgGivenMultiplerDuration, dmgTakenMultipler, dmgTakenMultiplerDuration, doubleStrikeChance, doubleStrikeDuration, bleedingChance, bleedingDuration, unblockable, fallback, descritptionFrameX, descriptionFrameY, descriptionLines, bmpPath, name, description));
				}
				else
					skillList->push_back(new Skill(flag, ID, cooldown, hp, hpRegen, hpRegenDuration, emp, empRegen, empRegenDuration, def, defMultipler, defMultiplerDuration, dmgGivenMultipler, dmgGivenMultiplerDuration, dmgTakenMultipler, dmgTakenMultiplerDuration, doubleStrikeChance, doubleStrikeDuration, bleedingChance, bleedingDuration, unblockable, fallback, descritptionFrameX, descriptionFrameY, descriptionLines, bmpPath, name, description, bmpXoffset, bmpYoffset, bmpMain));
				
				description = new vector<string>;
			}
			delete description;
			File.close();
		}
	}
	

	void Draw(Resources *resources, ALLEGRO_Font *allegro_font)
	{
		// calosc do przemyslenia jak zrobic zeby ladnie dzialalo w prostej petli

		// rysowanie menu wyboru umiejêtnoœci
		al_draw_filled_rectangle(0, 0, 720, 480, allegro_font->TRANSPARENT_BLACK3);
		al_draw_bitmap(resources->ui_eq, 30, 43, 0);

		if (selectedSkillIndex != -1) // docelowo kosz staje sie aktywny i mozna usunac przedmiot gdy zostanie zaznaczony
			al_draw_bitmap(resources->ui_bin, 53, 379, 0);

		al_draw_text(allegro_font->font20, allegro_font->ORANGE, 362, 50, ALLEGRO_ALIGN_CENTRE, "SKILLS");

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		al_draw_text(allegro_font->font18, allegro_font->LIGHT_YELLOW, 154, 80, ALLEGRO_ALIGN_CENTRE, "Offensive");

		////////////////////////////////////////////------------//////////////////////////////////////////////////
		al_draw_text(allegro_font->font12, allegro_font->WHITE, 154, 110, ALLEGRO_ALIGN_CENTRE, "Physical");
		al_draw_bitmap((*skillList)[9]->bmp, 79, 130, 0);
		al_draw_bitmap((*skillList)[10]->bmp, 134, 130, 0);
		al_draw_bitmap((*skillList)[11]->bmp, 189, 130, 0);

		////////////////////////////////////////////------------//////////////////////////////////////////////////
		al_draw_text(allegro_font->font12, allegro_font->WHITE, 154, 180, ALLEGRO_ALIGN_CENTRE, "Special");
		al_draw_bitmap((*skillList)[12]->bmp, 134, 200, 0);

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		al_draw_text(allegro_font->font18, allegro_font->LIGHT_YELLOW, 358, 80, ALLEGRO_ALIGN_CENTRE, "Defensive/Support");

		////////////////////////////////////////////------------//////////////////////////////////////////////////
		al_draw_text(allegro_font->font12, allegro_font->WHITE, 358, 110, ALLEGRO_ALIGN_CENTRE, "Aura");
		al_draw_bitmap((*skillList)[13]->bmp, 283, 130, 0);
		al_draw_bitmap((*skillList)[15]->bmp, 338, 130, 0);
		al_draw_bitmap((*skillList)[16]->bmp, 393, 130, 0);

		////////////////////////////////////////////------------//////////////////////////////////////////////////
		al_draw_text(allegro_font->font12, allegro_font->WHITE, 358, 180, ALLEGRO_ALIGN_CENTRE, "Warcry");
		al_draw_bitmap((*skillList)[14]->bmp, 283, 200, 0);
		al_draw_bitmap((*skillList)[17]->bmp, 338, 200, 0);

		////////////////////////////////////////////------------//////////////////////////////////////////////////
		al_draw_text(allegro_font->font12, allegro_font->WHITE, 358, 250, ALLEGRO_ALIGN_CENTRE, "Special");
		al_draw_bitmap((*skillList)[18]->bmp, 338, 270, 0);

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		al_draw_text(allegro_font->font18, allegro_font->LIGHT_YELLOW, 575, 80, ALLEGRO_ALIGN_CENTRE, "Potions");

		////////////////////////////////////////////------------//////////////////////////////////////////////////
		al_draw_text(allegro_font->font12, allegro_font->WHITE, 575, 110, ALLEGRO_ALIGN_CENTRE, "Healing");


		al_draw_scaled_bitmap((*skillList)[0]->bmp, 0, 0, 45, 45, 500, 130, 42, 42, 0);
		if ((*skillList)[0]->quantity == 0)
			al_draw_filled_rectangle(500, 130, 542, 172, allegro_font->TRANSPARENT_BLACK4);// RYSUJ CIEN

		al_draw_scaled_bitmap((*skillList)[1]->bmp, 0, 0, 45, 45, 555, 130, 42, 42, 0);
		if ((*skillList)[1]->quantity == 0)
			al_draw_filled_rectangle(555, 130, 597, 172, allegro_font->TRANSPARENT_BLACK4);// RYSUJ CIEN

		al_draw_scaled_bitmap((*skillList)[2]->bmp, 0, 0, 45, 45, 610, 130, 42, 42, 0);
		if ((*skillList)[2]->quantity == 0)
			al_draw_filled_rectangle(610, 130, 652, 172, allegro_font->TRANSPARENT_BLACK4);// RYSUJ CIEN

																					////////////////////////////////////////////------------//////////////////////////////////////////////////
		al_draw_text(allegro_font->font12, allegro_font->WHITE, 575, 180, ALLEGRO_ALIGN_CENTRE, "Energy");

		al_draw_scaled_bitmap((*skillList)[3]->bmp, 0, 0, 45, 45, 500, 200, 42, 42, 0);
		if ((*skillList)[3]->quantity == 0)
			al_draw_filled_rectangle(500, 200, 542, 242, allegro_font->TRANSPARENT_BLACK4);// RYSUJ CIEN

		al_draw_scaled_bitmap((*skillList)[4]->bmp, 0, 0, 45, 45, 555, 200, 42, 42, 0);
		if ((*skillList)[4]->quantity == 0)
			al_draw_filled_rectangle(555, 200, 597, 242, allegro_font->TRANSPARENT_BLACK4);// RYSUJ CIEN

		al_draw_scaled_bitmap((*skillList)[5]->bmp, 0, 0, 45, 45, 610, 200, 42, 42, 0);
		if ((*skillList)[5]->quantity == 0)
			al_draw_filled_rectangle(610, 200, 652, 242, allegro_font->TRANSPARENT_BLACK4);// RYSUJ CIEN

																					////////////////////////////////////////////------------//////////////////////////////////////////////////
		al_draw_text(allegro_font->font12, allegro_font->WHITE, 575, 250, ALLEGRO_ALIGN_CENTRE, "Mana");
		
		al_draw_scaled_bitmap((*skillList)[6]->bmp, 0, 0, 45, 45, 500, 270, 42, 42, 0);
		if ((*skillList)[6]->quantity == 0)
			al_draw_filled_rectangle(500, 270, 542, 312, allegro_font->TRANSPARENT_BLACK4);// RYSUJ CIEN

		al_draw_scaled_bitmap((*skillList)[7]->bmp, 0, 0, 45, 45, 555, 270, 42, 42, 0);
		if ((*skillList)[7]->quantity == 0)
			al_draw_filled_rectangle(555, 270, 597, 312, allegro_font->TRANSPARENT_BLACK4);// RYSUJ CIEN

		al_draw_scaled_bitmap((*skillList)[8]->bmp, 0, 0, 45, 45, 610, 270, 42, 42, 0);
		if ((*skillList)[8]->quantity == 0)
			al_draw_filled_rectangle(610, 270, 652, 312, allegro_font->TRANSPARENT_BLACK4);// RYSUJ CIEN

		////////////////////////////////////////////------------//////////////////////////////////////////////////
		//al_draw_textf(allegro_font->font12, al_map_rgb(255, 255, 255), 362, 405, ALLEGRO_ALIGN_CENTRE, "Select skill for #%d slot", 0);

	}

	Skill *GetSkill()
	{
		if (overlayedSkillIndex != -1)
			return skillList->at(overlayedSkillIndex);
		return nullptr;
	}

	int GetDescriptionDrawPosition() { return position; }

	void DrawDescription(int mouseX, int mouseY, Hero *hero, Skill *skill, ALLEGRO_Font *fonts, int y = 34)
	{

		if (overlayDock == false)
		{
			if (skill != nullptr)
			{
				if (position == 1) // draw to right side of cursor
				{
					al_draw_filled_rounded_rectangle(mouseX, mouseY - skill->descriptionFrameY, mouseX + skill->descriptionFrameX, mouseY, 8, 8, fonts->TRANSPARENT_BLACK5);
					al_draw_rounded_rectangle(mouseX, mouseY - skill->descriptionFrameY, mouseX + skill->descriptionFrameX, mouseY, 8, 8, fonts->TRANSPARENT_BLACK6, 2.5);
					al_draw_textf(fonts->font20, fonts->LIGHT_YELLOW, mouseX + skill->descriptionFrameX / 2, mouseY + 5 - skill->descriptionFrameY, ALLEGRO_ALIGN_CENTRE, "%s", skill->name.c_str());

					for (int i = 0; i < skill->description.size(); i++)
					{
						al_draw_textf(fonts->font12, fonts->WHITE, mouseX + skill->descriptionFrameX / 2, mouseY + y - skill->descriptionFrameY, ALLEGRO_ALIGN_CENTRE, skill->description[i].c_str());
						y += 16;
					}
					if (skill->flag == 0)
						al_draw_textf(fonts->font12, fonts->WHITE, mouseX + skill->descriptionFrameX / 2, mouseY + y - skill->descriptionFrameY, ALLEGRO_ALIGN_CENTRE, "Quantity: %d", skill->quantity);
				}
				else if (position == 3) // draw to left side of cursor
				{
					al_draw_filled_rounded_rectangle(mouseX - skill->descriptionFrameX, mouseY - skill->descriptionFrameY, mouseX, mouseY, 8, 8, fonts->TRANSPARENT_BLACK5);
					al_draw_rounded_rectangle(mouseX - skill->descriptionFrameX, mouseY - skill->descriptionFrameY, mouseX, mouseY, 8, 8, fonts->TRANSPARENT_BLACK6, 2.5);
					al_draw_textf(fonts->font20, fonts->LIGHT_YELLOW, mouseX - skill->descriptionFrameX / 2, mouseY + 5 - skill->descriptionFrameY, ALLEGRO_ALIGN_CENTRE, "%s", skill->name.c_str());

					for (int i = 0; i < skill->description.size(); i++)
					{
						al_draw_textf(fonts->font12, fonts->WHITE, mouseX - skill->descriptionFrameX / 2, mouseY + y - skill->descriptionFrameY, ALLEGRO_ALIGN_CENTRE, skill->description[i].c_str());
						y += 16;
					}
					if (skill->flag == 0)
						al_draw_textf(fonts->font12, fonts->WHITE, mouseX - skill->descriptionFrameX / 2, mouseY + y - skill->descriptionFrameY, ALLEGRO_ALIGN_CENTRE, "Quantity: %d", skill->quantity);
				}
				else if (position == 2) // draw to both sides of cursor
				{
					al_draw_filled_rounded_rectangle(mouseX - skill->descriptionFrameX / 2, mouseY - skill->descriptionFrameY, mouseX + skill->descriptionFrameX / 2, mouseY, 8, 8, fonts->TRANSPARENT_BLACK5);
					al_draw_rounded_rectangle(mouseX - skill->descriptionFrameX / 2, mouseY - skill->descriptionFrameY, mouseX + skill->descriptionFrameX / 2, mouseY, 8, 8, fonts->TRANSPARENT_BLACK6, 2.5);
					al_draw_textf(fonts->font20, fonts->LIGHT_YELLOW, mouseX, mouseY + 5 - skill->descriptionFrameY, ALLEGRO_ALIGN_CENTRE, "%s", skill->name.c_str());

					for (int i = 0; i < skill->description.size(); i++)
					{
						al_draw_textf(fonts->font12, fonts->WHITE, mouseX, mouseY + y - skill->descriptionFrameY, ALLEGRO_ALIGN_CENTRE, skill->description[i].c_str());
						y += 16;
					}
				}
			}		
		}
		else if (hero->eqDock[overlayedSkillIndex] != nullptr)
		{
			al_draw_filled_rounded_rectangle(mouseX - hero->eqDock[overlayedSkillIndex]->descriptionFrameX / 2, mouseY - hero->eqDock[overlayedSkillIndex]->descriptionFrameY, mouseX + hero->eqDock[overlayedSkillIndex]->descriptionFrameX / 2, mouseY, 8, 8, fonts->TRANSPARENT_BLACK5);
			al_draw_rounded_rectangle(mouseX - hero->eqDock[overlayedSkillIndex]->descriptionFrameX / 2, mouseY - hero->eqDock[overlayedSkillIndex]->descriptionFrameY, mouseX + hero->eqDock[overlayedSkillIndex]->descriptionFrameX / 2, mouseY, 8, 8, fonts->TRANSPARENT_BLACK6, 2.5);
			al_draw_textf(fonts->font20, fonts->LIGHT_YELLOW, mouseX, mouseY + 5 - hero->eqDock[overlayedSkillIndex]->descriptionFrameY, ALLEGRO_ALIGN_CENTRE, "%s", hero->eqDock[overlayedSkillIndex]->name.c_str());

			for (int i = 0; i < hero->eqDock[overlayedSkillIndex]->description.size(); i++)
			{
				al_draw_textf(fonts->font12, fonts->WHITE, mouseX, mouseY + y - hero->eqDock[overlayedSkillIndex]->descriptionFrameY, ALLEGRO_ALIGN_CENTRE, hero->eqDock[overlayedSkillIndex]->description[i].c_str());
				y += 16;
			}
			if (hero->eqDock[overlayedSkillIndex]->flag == 0)
				al_draw_textf(fonts->font12, fonts->WHITE, mouseX, mouseY + y - hero->eqDock[overlayedSkillIndex]->descriptionFrameY, ALLEGRO_ALIGN_CENTRE, "Quantity: %d", hero->eqDock[overlayedSkillIndex]->quantity);
		}
	}

	void DrawDockedSkills(int MouseX, int MouseY, Hero *hero, ALLEGRO_Font *fonts, bool openEquipment, bool openSkillTab)
	{	
		//this->selectedSkillIndex = 2;
		int dockX = 230;
		int dockY = 424;
		// WPROWADZONO RECZNE KOREKTY PRZY WSPOLRZEDNYCH X-owych

		if (hero->eqDock[0] != nullptr)
			al_draw_scaled_bitmap(hero->eqDock[0]->bmp, 0, 0, al_get_bitmap_width(hero->eqDock[0]->bmp), al_get_bitmap_height(hero->eqDock[0]->bmp), dockX, dockY, 42, 42, 0);
		if (hero->eqDock[1] != nullptr)
			al_draw_scaled_bitmap(hero->eqDock[1]->bmp, 0, 0, al_get_bitmap_width(hero->eqDock[1]->bmp), al_get_bitmap_height(hero->eqDock[1]->bmp), dockX + 43 + 1, dockY, 42, 42, 0);
		if (hero->eqDock[2] != nullptr)
			al_draw_scaled_bitmap(hero->eqDock[2]->bmp, 0, 0, al_get_bitmap_width(hero->eqDock[2]->bmp), al_get_bitmap_height(hero->eqDock[2]->bmp), dockX + 2 * 43 + 2, dockY, 42, 42, 0);
		if (hero->eqDock[3] != nullptr)
			al_draw_scaled_bitmap(hero->eqDock[3]->bmp, 0, 0, al_get_bitmap_width(hero->eqDock[3]->bmp), al_get_bitmap_height(hero->eqDock[3]->bmp), dockX + 3 * 43 + 2, dockY, 42, 42, 0);
		if (hero->eqDock[4] != nullptr)
			al_draw_scaled_bitmap(hero->eqDock[4]->bmp, 0, 0, al_get_bitmap_width(hero->eqDock[4]->bmp), al_get_bitmap_height(hero->eqDock[4]->bmp), dockX + 4 * 43 + 3, dockY, 42, 42, 0);
		if (hero->eqDock[5] != nullptr)
			al_draw_scaled_bitmap(hero->eqDock[5]->bmp, 0, 0, al_get_bitmap_width(hero->eqDock[5]->bmp), al_get_bitmap_height(hero->eqDock[5]->bmp), dockX + 5 * 43 + 5, dockY, 42, 42, 0);

		if (selectedFromTab == false)
		{
			if (selectedSkillIndex != -1 && openEquipment == false && openSkillTab == true)
				al_draw_filled_rectangle(229, 421, 491, 466, fonts->TRANSPARENT_BLACK4);
			switch (selectedSkillIndex)
			{
			case 0:
				al_draw_scaled_bitmap(hero->eqDock[selectedSkillIndex]->bmp, 0, 0, al_get_bitmap_width(hero->eqDock[selectedSkillIndex]->bmp), al_get_bitmap_height(hero->eqDock[selectedSkillIndex]->bmp), dockX, dockY, 42, 42, 0);
				break;
			case 1:
				al_draw_scaled_bitmap(hero->eqDock[selectedSkillIndex]->bmp, 0, 0, al_get_bitmap_width(hero->eqDock[selectedSkillIndex]->bmp), al_get_bitmap_height(hero->eqDock[selectedSkillIndex]->bmp), dockX + 43 + 1, dockY, 42, 42, 0);
				break;
			case 2:
				al_draw_scaled_bitmap(hero->eqDock[selectedSkillIndex]->bmp, 0, 0, al_get_bitmap_width(hero->eqDock[selectedSkillIndex]->bmp), al_get_bitmap_height(hero->eqDock[selectedSkillIndex]->bmp), dockX + 2 * 43 + 2, dockY, 42, 42, 0);
				break;
			case 3:
				al_draw_scaled_bitmap(hero->eqDock[selectedSkillIndex]->bmp, 0, 0, al_get_bitmap_width(hero->eqDock[selectedSkillIndex]->bmp), al_get_bitmap_height(hero->eqDock[selectedSkillIndex]->bmp), dockX + 3 * 43 + 2, dockY, 42, 42, 0);
				break;
			case 4:
				al_draw_scaled_bitmap(hero->eqDock[selectedSkillIndex]->bmp, 0, 0, al_get_bitmap_width(hero->eqDock[selectedSkillIndex]->bmp), al_get_bitmap_height(hero->eqDock[selectedSkillIndex]->bmp), dockX + 4 * 43 + 3, dockY, 42, 42, 0);
				break;
			case 5:
				al_draw_scaled_bitmap(hero->eqDock[selectedSkillIndex]->bmp, 0, 0, al_get_bitmap_width(hero->eqDock[selectedSkillIndex]->bmp), al_get_bitmap_height(hero->eqDock[selectedSkillIndex]->bmp), dockX + 5 * 43 + 5, dockY, 42, 42, 0);
				break;
			default:
				break;
			}
		}
	}

	void DrawSelectedSkill(int MouseX, int MouseY, Hero *hero)
	{
		if (selectedSkillIndex != -1)
		{
			if (selectedFromTab == true)
			{
				if ((*skillList)[selectedSkillIndex] != nullptr)
					al_draw_bitmap((*skillList)[selectedSkillIndex]->bmp, MouseX - 45, MouseY - 45, 0);
			}
			else
			{
				if (hero->eqDock[selectedSkillIndex] != nullptr)
					al_draw_bitmap(hero->eqDock[selectedSkillIndex]->bmp, MouseX - 45, MouseY - 45, 0);
			}
		}		
	}

	void AquireSkill(Hero *hero)
	{
		hero->eqDock[0] = skillList->at(9);		//normal attack
		hero->eqDock[3] = skillList->at(0);		//health potion
		hero->eqDock[4] = skillList->at(3);		//energy potion
		hero->eqDock[5] = skillList->at(18);	//escape

		skillList->at(0)->quantity = 5;
		skillList->at(3)->quantity = 5;

	}

	void ProceedSelection(Hero *hero, int slot, bool LMBPressed, bool ToDock)
	{
		if (LMBPressed == true)
		{
			if (selectedFromTab == false)
			{
				if (ToDock == true)
				{
					if (selectedSkill == nullptr)
					{
						if (hero->eqDock[overlayedSkillIndex] != nullptr)
						{
							selectedSkillIndex = slot;
							selectedSkill = hero->eqDock[selectedSkillIndex];
						}
					}
					else if (selectedSkill == hero->eqDock[overlayedSkillIndex])
					{
						selectedSkillIndex = -1;
						selectedSkill = nullptr;
					}
					else
					{
						Skill *tmp = hero->eqDock[overlayedSkillIndex];
						hero->eqDock[overlayedSkillIndex] = selectedSkill;
						hero->eqDock[selectedSkillIndex] = tmp;
						selectedSkillIndex = -1;
						selectedSkill = nullptr;
					}
				}
				else
				{
					if (selectedSkill == nullptr)
					{
						selectedSkillIndex = slot;
						selectedFromTab = true;
						selectedSkill = skillList->at(overlayedSkillIndex);
					}
					else
					{
						hero->eqDock[selectedSkillIndex] = skillList->at(overlayedSkillIndex);
						selectedSkillIndex = -1;
						selectedSkill = nullptr;
					}
				}
			}
			else
			{
				if (ToDock == true)
				{
					hero->eqDock[overlayedSkillIndex] = skillList->at(selectedSkillIndex);
					selectedSkillIndex = -1;
					selectedSkill = nullptr;
					selectedFromTab = false;
				}
				else
				{
					if(selectedSkillIndex == slot)
					{
						selectedSkillIndex = -1;
						selectedSkill = nullptr;
						selectedFromTab = false;
					}
					else
					{
						selectedSkillIndex = slot;
						selectedFromTab = true;
						selectedSkill = skillList->at(selectedSkillIndex);
					}
				}
			}		
		}		
	}

	void CheckCursorOverlayDockAndClick(int mouseX, int mouseY, Hero *hero, bool LMBPressed, bool SkillTabOpen) // funkcja jest 'nieelegancko' wykonana ze wzgledu na ograniczenia czasowe
	{
		int dockX = 230;
		int dockY = 424;

		if (mouseX >= dockX && mouseX <= dockX + 5 * 43 + 5 + 42 && mouseY >= dockY && mouseY <= mouseY + 42)
		{
			overlayDock = true;

			if (mouseX >= dockX && mouseX <= dockX + 42)
			{
				overlayedSkillIndex = 0;
				if (SkillTabOpen == true)
					ProceedSelection(hero, 0, LMBPressed, true);
			}
			else if (mouseX >= dockX + 43 + 1 && mouseX <= dockX + 43 + 1 + 42)
			{
				overlayedSkillIndex = 1;
				if (SkillTabOpen == true)
					ProceedSelection(hero, 1, LMBPressed, true);
			}
			else if (mouseX >= dockX + 2 * 43 + 2 && mouseX <= dockX + 2 * 43 + 2 + 42)
			{
				overlayedSkillIndex = 2;
				if (SkillTabOpen == true)
					ProceedSelection(hero, 2, LMBPressed, true);
			}
			else if (mouseX >= dockX + 3 * 43 + 2 && mouseX <= dockX + 3 * 43 + 2 + 42)
			{
				overlayedSkillIndex = 3;
				if (SkillTabOpen == true)
					ProceedSelection(hero, 3, LMBPressed, true);
			}
			else if (mouseX >= dockX + 4 * 43 + 3 && mouseX <= dockX + 4 * 43 + 3 + 42)
			{
				overlayedSkillIndex = 4;
				if (SkillTabOpen == true)
					ProceedSelection(hero, 4, LMBPressed, true);
			}
			else
			{
				overlayedSkillIndex = 5;
				if (SkillTabOpen == true)
					ProceedSelection(hero, 5, LMBPressed, true);
			}
		}

		else
			overlayDock = false;
	}
	
	void CheckCursorOverlayTabAndClick(int mouseX, int mouseY, Hero *hero, bool LMBPressed) // funkcja jest 'nieelegancko' wykonana ze wzgledu na ograniczenia czasowe
	{
		overlayDock = false;
			if (mouseX >= 79 && mouseX <= 121 && mouseY >= 130 && mouseY <= 172)	// 1W-1S - skill nr 10
			{
				overlayedSkillIndex = 9;
				position = RIGHT;

				ProceedSelection(hero, 9, LMBPressed, false);
			}
			else if (mouseX >= 134 && mouseX <= 176 && mouseY >= 130 && mouseY <= 172)	// 1W-2S - skill nr 11
			{
				overlayedSkillIndex = 10;
				position = RIGHT;

				ProceedSelection(hero, 10, LMBPressed, false);
			}
			else if (mouseX >= 189 && mouseX <= 231 && mouseY >= 130 && mouseY <= 172)	// 1W-3S - skill nr 12
			{
				overlayedSkillIndex = 11;
				position = RIGHT;
				ProceedSelection(hero, 11, LMBPressed, false);
			}
			else if (mouseX >= 283 && mouseX <= 325 && mouseY >= 130 && mouseY <= 172)	// 1W-4S - skill nr 14
			{
				overlayedSkillIndex = 13;
				position = MIDDLE;

				ProceedSelection(hero, 13, LMBPressed, false);
			}
			else if (mouseX >= 338 && mouseX <= 380 && mouseY >= 130 && mouseY <= 172)	// 1W-5S - skill nr 16
			{
				overlayedSkillIndex = 15;
				position = MIDDLE;

				ProceedSelection(hero, 15, LMBPressed, false);
			}
			else if (mouseX >= 393 && mouseX <= 435 && mouseY >= 130 && mouseY <= 172)	// 1W-6S - skill nr 17
			{
				overlayedSkillIndex = 16;
				position = MIDDLE;

				ProceedSelection(hero, 16, LMBPressed, false);
			}
			else if (mouseX >= 500 && mouseX <= 542 && mouseY >= 130 && mouseY <= 172)	// 1W-7S - skill nr 1
			{
				overlayedSkillIndex = 0;
				position = LEFT;

				ProceedSelection(hero, 0, LMBPressed, false);
			}
			else if (mouseX >= 555 && mouseX <= 597 && mouseY >= 130 && mouseY <= 172)	// 1W-8S - skill nr 2
			{
				overlayedSkillIndex = 1;
				position = LEFT;

				ProceedSelection(hero, 1, LMBPressed, false);
			}
			else if (mouseX >= 610 && mouseX <= 652 && mouseY >= 130 && mouseY <= 172)	// 1W-9S - skill nr 3
			{
				overlayedSkillIndex = 2;
				position = LEFT;

				ProceedSelection(hero, 2, LMBPressed, false);
			}
			else if (mouseX >= 79 && mouseX <= 121 && mouseY >= 200 && mouseY <= 242)	// 2W-1S - puste miejsce na umiejetnosc
			{
				;

			}
			else if (mouseX >= 134 && mouseX <= 176 && mouseY >= 200 && mouseY <= 242)	// 2W-2S - skill nr 13
			{
				overlayedSkillIndex = 12;
				position = RIGHT;

				ProceedSelection(hero, 12, LMBPressed, false);
			}
			else if (mouseX >= 189 && mouseX <= 231 && mouseY >= 200 && mouseY <= 242)	// 2W-3S - puste miejsce na umiejetnosc
			{
				;

			}
			else if (mouseX >= 283 && mouseX <= 325 && mouseY >= 200 && mouseY <= 242)	// 2W-4S - skill nr 15
			{
				overlayedSkillIndex = 14;
				position = MIDDLE;

				ProceedSelection(hero, 14, LMBPressed, false);
			}
			else if (mouseX >= 338 && mouseX <= 380 && mouseY >= 200 && mouseY <= 242)	// 2W-5S - skill nr 18
			{
				overlayedSkillIndex = 17;
				position = MIDDLE;

				ProceedSelection(hero, 17, LMBPressed, false);
			}
			else if (mouseX >= 393 && mouseX <= 435 && mouseY >= 200 && mouseY <= 242)	// 2W-6S - puste miejsce na umiejetnosc
			{
				;

			}
			else if (mouseX >= 500 && mouseX <= 542 && mouseY >= 200 && mouseY <= 242)	// 2W-7S - skill nr 4
			{
				overlayedSkillIndex = 3;
				position = LEFT;

				ProceedSelection(hero, 3, LMBPressed, false);
			}
			else if (mouseX >= 555 && mouseX <= 597 && mouseY >= 200 && mouseY <= 242)	// 2W-8S - skill nr 5
			{
				overlayedSkillIndex = 4;
				position = LEFT;

				ProceedSelection(hero, 4, LMBPressed, false);
			}
			else if (mouseX >= 610 && mouseX <= 652 && mouseY >= 200 && mouseY <= 242)	// 2W-9S - skill nr 6
			{
				overlayedSkillIndex = 5;
				position = LEFT;

				ProceedSelection(hero, 5, LMBPressed, false);
			}
			else if (mouseX >= 79 && mouseX <= 121 && mouseY >= 270 && mouseY <= 312)	// 3W-1S - puste miejsce na umiejetnosc
			{
				;

			}
			else if (mouseX >= 134 && mouseX <= 176 && mouseY >= 270 && mouseY <= 312)	// 3W-2S - puste miejsce na umiejetnosc
			{
				;

			}
			else if (mouseX >= 189 && mouseX <= 231 && mouseY >= 270 && mouseY <= 312)	// 3W-3S - puste miejsce na umiejetnosc
			{
				;

			}
			else if (mouseX >= 283 && mouseX <= 325 && mouseY >= 270 && mouseY <= 312)	// 3W-4S - puste miejsce na umiejetnosc
			{
				;

			}
			else if (mouseX >= 338 && mouseX <= 380 && mouseY >= 270 && mouseY <= 312)	// 3W-5S - skill nr 19
			{
				overlayedSkillIndex = 18;
				position = MIDDLE;

				ProceedSelection(hero, 18, LMBPressed, false);
			}
			else if (mouseX >= 393 && mouseX <= 435 && mouseY >= 270 && mouseY <= 312)	// 3W-6S - puste miejsce na umiejetnosc
			{
				;

			}
			else if (mouseX >= 500 && mouseX <= 542 && mouseY >= 270 && mouseY <= 312)	// 3W-7S - skill nr 7
			{
				overlayedSkillIndex = 6;
				position = LEFT;

				ProceedSelection(hero, 6, LMBPressed, false);

			}
			else if (mouseX >= 555 && mouseX <= 597 && mouseY >= 270 && mouseY <= 312)	// 3W-8S - skill nr 8
			{
				overlayedSkillIndex = 7;
				position = LEFT;

				ProceedSelection(hero, 7, LMBPressed, false);
			}
			else if (mouseX >= 610 && mouseX <= 652 && mouseY >= 270 && mouseY <= 312)	// 3W-9S - skill nr 9
			{
				overlayedSkillIndex = 8;
				position = LEFT;

				ProceedSelection(hero, 8, LMBPressed, false);
			}
			else 
				overlayedSkillIndex = -1;	
	}

	bool CheckButtons(int mouseX, int mouseY, Hero *hero, bool LMBPressed)
	{
		if (LMBPressed)
		{
			if (mouseX >= 54 && mouseX <= 80 && mouseY <= 407 && mouseY >= 380)
			{
				if (selectedSkillIndex != -1)
				{
					if (selectedFromTab == false)
						hero->eqDock[selectedSkillIndex] = nullptr;

					selectedFromTab = false;
					selectedSkillIndex = -1;
					selectedSkill = nullptr;
				}
			}

			if (mouseX >= 638 && mouseX <= 664 && mouseY >= 380 && mouseY <= 407)
			{
				ResetSkillTab();
				return false;
			}
		}
		return true;
	}

	void ResetSkillTab()
	{
		selectedSkill = nullptr;
		overlayedSkillIndex = -1;
		selectedSkillIndex = -1;
		selectedFromTab = false;
		overlayDock = false;
		position = NONE;
	}

	void DropPotions()
	{
		int result = 1 + rand() % 100;

		if (result % 5 == 0)
		{
			skillList->at(1)->quantity += 1 + rand() % 5;
			skillList->at(4)->quantity += 1 + rand() % 5;
			skillList->at(7)->quantity += 1 + rand() % 5;
		}
		else if (result % 7 == 0)
		{
			skillList->at(2)->quantity += 1 + rand() % 2;
			skillList->at(5)->quantity += 1 + rand() % 2;
			skillList->at(8)->quantity += 1 + rand() % 2;
		}
		else
		{
			skillList->at(0)->quantity += 1 + rand() % 10;
			skillList->at(3)->quantity += 1 + rand() % 10;
			skillList->at(6)->quantity += 1 + rand() % 10;
		}

	}
};