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
	int overlayedSkillIndex;
	int selectedSkillIndex;
	enum PositionToDrawDescription
	{
		NONE, RIGHT, MIDDLE, LEFT
	} position;

public:
	ManagerSkill() : Manager()
	{
		skillList = nullptr;
		bmpMain = al_load_bitmap("data//skill//bmp//skillTable.png");
		overlayedSkillIndex = -1;
		selectedSkillIndex = -1;	
		position = NONE;
	}
	~ManagerSkill()
	{
		//skillList->erase(skillList->begin(), skillList->end());
		//delete skillList;

		for (int i = 0; i < skillList->size(); i++)
		{
			Skill* element = skillList->at(i);
			delete element;
		}
		delete skillList;

		/*while (!skillList->empty())
		{
			Skill* element = skillList->pop_back();
			skillList->;
			delete element;
		}
		delete skillList;*/

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
	

	virtual void Draw(Hero *hero, Resources *resources, ALLEGRO_Font *allegro_font)
	{
		// calosc do przemyslenia jak zrobic zeby ladnie dzialalo w prostej petli

		// rysowanie menu wyboru umiejêtnoœci
		al_draw_filled_rectangle(0, 0, 720, 480, al_map_rgba(0, 0, 0, 175));
		al_draw_bitmap(resources->ui_eq, 30, 43, 0);


		al_draw_text(allegro_font->font20, al_map_rgb(255, 142, 0), 362, 50, ALLEGRO_ALIGN_CENTRE, "SKILLS");

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		al_draw_text(allegro_font->font18, al_map_rgb(240, 230, 140), 154, 80, ALLEGRO_ALIGN_CENTRE, "Offensive");

		////////////////////////////////////////////------------//////////////////////////////////////////////////
		al_draw_text(allegro_font->font12, al_map_rgb(255, 255, 255), 154, 110, ALLEGRO_ALIGN_CENTRE, "Physical");
		al_draw_bitmap((*skillList)[9]->bmp, 79, 130, 0);
		al_draw_bitmap((*skillList)[10]->bmp, 134, 130, 0);
		al_draw_bitmap((*skillList)[11]->bmp, 189, 130, 0);

		////////////////////////////////////////////------------//////////////////////////////////////////////////
		al_draw_text(allegro_font->font12, al_map_rgb(255, 255, 255), 154, 180, ALLEGRO_ALIGN_CENTRE, "Special");
		al_draw_bitmap((*skillList)[12]->bmp, 134, 200, 0);

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		al_draw_text(allegro_font->font18, al_map_rgb(240, 230, 140), 358, 80, ALLEGRO_ALIGN_CENTRE, "Defensive/Support");

		////////////////////////////////////////////------------//////////////////////////////////////////////////
		al_draw_text(allegro_font->font12, al_map_rgb(255, 255, 255), 358, 110, ALLEGRO_ALIGN_CENTRE, "Aura");
		al_draw_bitmap((*skillList)[13]->bmp, 283, 130, 0);
		al_draw_bitmap((*skillList)[15]->bmp, 338, 130, 0);
		al_draw_bitmap((*skillList)[16]->bmp, 393, 130, 0);

		////////////////////////////////////////////------------//////////////////////////////////////////////////
		al_draw_text(allegro_font->font12, al_map_rgb(255, 255, 255), 358, 180, ALLEGRO_ALIGN_CENTRE, "Warcry");
		al_draw_bitmap((*skillList)[14]->bmp, 283, 200, 0);
		al_draw_bitmap((*skillList)[17]->bmp, 338, 200, 0);

		////////////////////////////////////////////------------//////////////////////////////////////////////////
		al_draw_text(allegro_font->font12, al_map_rgb(255, 255, 255), 358, 250, ALLEGRO_ALIGN_CENTRE, "Special");
		al_draw_bitmap((*skillList)[18]->bmp, 338, 270, 0);

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		al_draw_text(allegro_font->font18, al_map_rgb(240, 230, 140), 575, 80, ALLEGRO_ALIGN_CENTRE, "Potions");

		////////////////////////////////////////////------------//////////////////////////////////////////////////
		al_draw_text(allegro_font->font12, al_map_rgb(255, 255, 255), 575, 110, ALLEGRO_ALIGN_CENTRE, "Healing");


		al_draw_scaled_bitmap((*skillList)[0]->bmp, 0, 0, 45, 45, 500, 130, 42, 42, 0);
		if ((*skillList)[0]->quantity == 0)
			al_draw_filled_rectangle(500, 130, 542, 172, al_map_rgba(0, 0, 0, 210));// RYSUJ CIEN

		al_draw_scaled_bitmap((*skillList)[1]->bmp, 0, 0, 45, 45, 555, 130, 42, 42, 0);
		if ((*skillList)[1]->quantity == 0)
			al_draw_filled_rectangle(555, 130, 597, 172, al_map_rgba(0, 0, 0, 210));// RYSUJ CIEN

		al_draw_scaled_bitmap((*skillList)[2]->bmp, 0, 0, 45, 45, 610, 130, 42, 42, 0);
		if ((*skillList)[2]->quantity == 0)
			al_draw_filled_rectangle(610, 130, 652, 172, al_map_rgba(0, 0, 0, 210));// RYSUJ CIEN

																					////////////////////////////////////////////------------//////////////////////////////////////////////////
		al_draw_text(allegro_font->font12, al_map_rgb(255, 255, 255), 575, 180, ALLEGRO_ALIGN_CENTRE, "Energy");

		al_draw_scaled_bitmap((*skillList)[3]->bmp, 0, 0, 45, 45, 500, 200, 42, 42, 0);
		if ((*skillList)[3]->quantity == 0)
			al_draw_filled_rectangle(500, 200, 542, 242, al_map_rgba(0, 0, 0, 210));// RYSUJ CIEN

		al_draw_scaled_bitmap((*skillList)[4]->bmp, 0, 0, 45, 45, 555, 200, 42, 42, 0);
		if ((*skillList)[4]->quantity == 0)
			al_draw_filled_rectangle(555, 200, 597, 242, al_map_rgba(0, 0, 0, 210));// RYSUJ CIEN

		al_draw_scaled_bitmap((*skillList)[5]->bmp, 0, 0, 45, 45, 610, 200, 42, 42, 0);
		if ((*skillList)[5]->quantity == 0)
			al_draw_filled_rectangle(610, 200, 652, 242, al_map_rgba(0, 0, 0, 210));// RYSUJ CIEN

																					////////////////////////////////////////////------------//////////////////////////////////////////////////
		al_draw_text(allegro_font->font12, al_map_rgb(255, 255, 255), 575, 250, ALLEGRO_ALIGN_CENTRE, "Mana");
		
		al_draw_scaled_bitmap((*skillList)[6]->bmp, 0, 0, 45, 45, 500, 270, 42, 42, 0);
		if ((*skillList)[6]->quantity == 0)
			al_draw_filled_rectangle(500, 270, 542, 312, al_map_rgba(0, 0, 0, 210));// RYSUJ CIEN

		al_draw_scaled_bitmap((*skillList)[7]->bmp, 0, 0, 45, 45, 555, 270, 42, 42, 0);
		if ((*skillList)[7]->quantity == 0)
			al_draw_filled_rectangle(555, 270, 597, 312, al_map_rgba(0, 0, 0, 210));// RYSUJ CIEN

		al_draw_scaled_bitmap((*skillList)[8]->bmp, 0, 0, 45, 45, 610, 270, 42, 42, 0);
		if ((*skillList)[8]->quantity == 0)
			al_draw_filled_rectangle(610, 270, 652, 312, al_map_rgba(0, 0, 0, 210));// RYSUJ CIEN

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

	void DrawDescription(int mouseX, int mouseY, Skill *skill, ALLEGRO_Font *fonts, int y = 34)
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

	void CheckCursorOverlayAndClick(int mouseX, int mouseY) // funkcja jest 'nieelegancko' wykonana ze wzgledu na ograniczenia czasowe
	{
		//if (mouseX >= 79 && mouseX <= 652 && mouseY >= 130 && mouseY <= 172)
		//{
			if (mouseX >= 79 && mouseX <= 121 && mouseY >= 130 && mouseY <= 172)	// 1W-1S - skill nr 10
			{
				overlayedSkillIndex = 9;
				position = RIGHT;
				//item_skill_description(10, mousex, mousey, potion_skill, y, font20, font12, 1, al_map_rgba(0, 0, 0, 245));
				//if (ITEM_SELECTED_DOCK != 0 && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1)
				//{
				//	eq_dock[ITEM_SELECTED_DOCK - 1] = potion_skill[9];
				//	ITEM_SELECTED_DOCK = 0;
				//}
			}
			else if (mouseX >= 134 && mouseX <= 176 && mouseY >= 130 && mouseY <= 172)	// 1W-2S - skill nr 11
			{
				overlayedSkillIndex = 10;
				position = RIGHT;
				//item_skill_description(11, mousex, mousey, potion_skill, y, font20, font12, 1, al_map_rgba(0, 0, 0, 245));
				//if (ITEM_SELECTED_DOCK != 0 && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1)
				//{
				//	eq_dock[ITEM_SELECTED_DOCK - 1] = potion_skill[10];
				//	ITEM_SELECTED_DOCK = 0;
				//}

			}
			else if (mouseX >= 189 && mouseX <= 231 && mouseY >= 130 && mouseY <= 172)	// 1W-3S - skill nr 12
			{
				overlayedSkillIndex = 11;
				position = RIGHT;
				/*item_skill_description(12, mousex, mousey, potion_skill, y, font20, font12, 1, al_map_rgba(0, 0, 0, 245));
				if (ITEM_SELECTED_DOCK != 0 && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1)
				{
					eq_dock[ITEM_SELECTED_DOCK - 1] = potion_skill[11];
					ITEM_SELECTED_DOCK = 0;
				}*/
			}
			else if (mouseX >= 283 && mouseX <= 325 && mouseY >= 130 && mouseY <= 172)	// 1W-4S - skill nr 14
			{
				overlayedSkillIndex = 13;
				position = MIDDLE;
				/*item_skill_description(14, mousex, mousey, potion_skill, y, font20, font12, 2, al_map_rgba(0, 0, 0, 245));
				if (ITEM_SELECTED_DOCK != 0 && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1)
				{
					eq_dock[ITEM_SELECTED_DOCK - 1] = potion_skill[13];
					ITEM_SELECTED_DOCK = 0;
				}*/
			}
			else if (mouseX >= 338 && mouseX <= 380 && mouseY >= 130 && mouseY <= 172)	// 1W-5S - skill nr 16
			{
				overlayedSkillIndex = 15;
				position = MIDDLE;
				/*item_skill_description(16, mousex, mousey, potion_skill, y, font20, font12, 2, al_map_rgba(0, 0, 0, 245));
				if (ITEM_SELECTED_DOCK != 0 && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1)
				{
					eq_dock[ITEM_SELECTED_DOCK - 1] = potion_skill[15];
					ITEM_SELECTED_DOCK = 0;
				}*/
			}
			else if (mouseX >= 393 && mouseX <= 435 && mouseY >= 130 && mouseY <= 172)	// 1W-6S - skill nr 17
			{
				overlayedSkillIndex = 16;
				position = MIDDLE;
				/*item_skill_description(17, mousex, mousey, potion_skill, y, font20, font12, 2, al_map_rgba(0, 0, 0, 245));
				if (ITEM_SELECTED_DOCK != 0 && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1)
				{
					eq_dock[ITEM_SELECTED_DOCK - 1] = potion_skill[16];
					ITEM_SELECTED_DOCK = 0;
				}*/
			}
			else if (mouseX >= 500 && mouseX <= 542 && mouseY >= 130 && mouseY <= 172)	// 1W-7S - skill nr 1
			{
				overlayedSkillIndex = 0;
				position = LEFT;
				/*item_skill_description(1, mousex, mousey, potion_skill, y, font20, font12, 3, al_map_rgba(0, 0, 0, 245));
				if (ITEM_SELECTED_DOCK != 0 && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1)
				{
					if (potion_skill[0].quantity > 0)
					{
						eq_dock[ITEM_SELECTED_DOCK - 1] = potion_skill[0];
						ITEM_SELECTED_DOCK = 0;
					}
				}*/
			}
			else if (mouseX >= 555 && mouseX <= 597 && mouseY >= 130 && mouseY <= 172)	// 1W-8S - skill nr 2
			{
				overlayedSkillIndex = 1;
				position = LEFT;
				/*item_skill_description(2, mousex, mousey, potion_skill, y, font20, font12, 3, al_map_rgba(0, 0, 0, 245));
				if (ITEM_SELECTED_DOCK != 0 && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1)
				{
					if (potion_skill[1].quantity > 0)
					{
						eq_dock[ITEM_SELECTED_DOCK - 1] = potion_skill[1];
						ITEM_SELECTED_DOCK = 0;
					}
				}*/
			}
			else if (mouseX >= 610 && mouseX <= 652 && mouseY >= 130 && mouseY <= 172)	// 1W-9S - skill nr 3
			{
				overlayedSkillIndex = 2;
				position = LEFT;
				/*item_skill_description(3, mousex, mousey, potion_skill, y, font20, font12, 3, al_map_rgba(0, 0, 0, 245));
				if (ITEM_SELECTED_DOCK != 0 && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1)
				{
					if (potion_skill[2].quantity > 0)
					{
						eq_dock[ITEM_SELECTED_DOCK - 1] = potion_skill[2];
						ITEM_SELECTED_DOCK = 0;
					}
				}*/
			}
		//}
		//else if (mouseX >= 79 && mouseX <= 652 && mouseY >= 200 && mouseY <= 242)
		//{
			else if (mouseX >= 79 && mouseX <= 121 && mouseY >= 200 && mouseY <= 242)	// 2W-1S - puste miejsce na umiejetnosc
			{
				;

			}
			else if (mouseX >= 134 && mouseX <= 176 && mouseY >= 200 && mouseY <= 242)	// 2W-2S - skill nr 13
			{
				overlayedSkillIndex = 12;
				position = RIGHT;
				//item_skill_description(13, mousex, mousey, potion_skill, y, font20, font12, 1, al_map_rgba(0, 0, 0, 245));
				//if (ITEM_SELECTED_DOCK != 0 && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1)
				//{
				//	eq_dock[ITEM_SELECTED_DOCK - 1] = potion_skill[12];
				//	ITEM_SELECTED_DOCK = 0;
				//}
			}
			else if (mouseX >= 189 && mouseX <= 231 && mouseY >= 200 && mouseY <= 242)	// 2W-3S - puste miejsce na umiejetnosc
			{
				;

			}
			else if (mouseX >= 283 && mouseX <= 325 && mouseY >= 200 && mouseY <= 242)	// 2W-4S - skill nr 15
			{
				overlayedSkillIndex = 14;
				position = MIDDLE;
				/*item_skill_description(15, mousex, mousey, potion_skill, y, font20, font12, 2, al_map_rgba(0, 0, 0, 245));
				if (ITEM_SELECTED_DOCK != 0 && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1)
				{
					eq_dock[ITEM_SELECTED_DOCK - 1] = potion_skill[14];
					ITEM_SELECTED_DOCK = 0;
				}*/
			}
			else if (mouseX >= 338 && mouseX <= 380 && mouseY >= 200 && mouseY <= 242)	// 2W-5S - skill nr 18
			{
				overlayedSkillIndex = 17;
				position = MIDDLE;
				/*item_skill_description(18, mousex, mousey, potion_skill, y, font20, font12, 2, al_map_rgba(0, 0, 0, 245));
				if (ITEM_SELECTED_DOCK != 0 && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1)
				{
					eq_dock[ITEM_SELECTED_DOCK - 1] = potion_skill[17];
					ITEM_SELECTED_DOCK = 0;
				}*/
			}
			else if (mouseX >= 393 && mouseX <= 435 && mouseY >= 200 && mouseY <= 242)	// 2W-6S - puste miejsce na umiejetnosc
			{
				;

			}
			else if (mouseX >= 500 && mouseX <= 542 && mouseY >= 200 && mouseY <= 242)	// 2W-7S - skill nr 4
			{
				overlayedSkillIndex = 3;
				position = LEFT;
				/*item_skill_description(4, mousex, mousey, potion_skill, y, font20, font12, 3, al_map_rgba(0, 0, 0, 245));
				if (ITEM_SELECTED_DOCK != 0 && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1)
				{
					if (potion_skill[3].quantity > 0)
					{
						eq_dock[ITEM_SELECTED_DOCK - 1] = potion_skill[3];
						ITEM_SELECTED_DOCK = 0;
					}
				}*/
			}
			else if (mouseX >= 555 && mouseX <= 597 && mouseY >= 200 && mouseY <= 242)	// 2W-8S - skill nr 5
			{
				overlayedSkillIndex = 4;
				position = LEFT;
				/*item_skill_description(5, mousex, mousey, potion_skill, y, font20, font12, 3, al_map_rgba(0, 0, 0, 245));
				if (ITEM_SELECTED_DOCK != 0 && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1)
				{
					if (potion_skill[4].quantity > 0)
					{
						eq_dock[ITEM_SELECTED_DOCK - 1] = potion_skill[4];
						ITEM_SELECTED_DOCK = 0;
					}
				}*/
			}
			else if (mouseX >= 610 && mouseX <= 652 && mouseY >= 200 && mouseY <= 242)	// 2W-9S - skill nr 6
			{
				overlayedSkillIndex = 5;
				position = LEFT;
				/*item_skill_description(6, mousex, mousey, potion_skill, y, font20, font12, 3, al_map_rgba(0, 0, 0, 245));
				if (ITEM_SELECTED_DOCK != 0 && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1)
				{
					if (potion_skill[5].quantity > 0)
					{
						eq_dock[ITEM_SELECTED_DOCK - 1] = potion_skill[5];
						ITEM_SELECTED_DOCK = 0;
					}
				}*/
			}
		//}
		//else if (mouseX >= 79 && mouseX <= 652 && mouseY >= 270 && mouseY <= 312)
		//{
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
				/*item_skill_description(19, mousex, mousey, potion_skill, y, font20, font12, 2, al_map_rgba(0, 0, 0, 245));
				if (ITEM_SELECTED_DOCK != 0 && ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1)
				{
					eq_dock[ITEM_SELECTED_DOCK - 1] = potion_skill[18];
					ITEM_SELECTED_DOCK = 0;
				}*/
			}
			else if (mouseX >= 393 && mouseX <= 435 && mouseY >= 270 && mouseY <= 312)	// 3W-6S - puste miejsce na umiejetnosc
			{
				;

			}
			else if (mouseX >= 500 && mouseX <= 542 && mouseY >= 270 && mouseY <= 312)	// 3W-7S - skill nr 7
			{
				overlayedSkillIndex = 6;
				position = LEFT;
				//item_skill_description(7, mousex, mousey, potion_skill, y, font20, font12, 3, al_map_rgba(0, 0, 0, 245));

			}
			else if (mouseX >= 555 && mouseX <= 597 && mouseY >= 270 && mouseY <= 312)	// 3W-8S - skill nr 8
			{
				overlayedSkillIndex = 7;
				position = LEFT;
				//item_skill_description(8, mousex, mousey, potion_skill, y, font20, font12, 3, al_map_rgba(0, 0, 0, 245));

			}
			else if (mouseX >= 610 && mouseX <= 652 && mouseY >= 270 && mouseY <= 312)	// 3W-9S - skill nr 9
			{
				overlayedSkillIndex = 8;
				position = LEFT;
				//item_skill_description(9, mousex, mousey, potion_skill, y, font20, font12, 3, al_map_rgba(0, 0, 0, 245));

			}
			else overlayedSkillIndex = -1;
		//}
		
	}
};