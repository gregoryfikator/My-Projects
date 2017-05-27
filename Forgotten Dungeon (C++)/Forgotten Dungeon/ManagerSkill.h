#pragma once
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include "Skill.h"

using namespace std;

class ManagerSkill
{
	vector<Skill *> *skillList;

public:
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
		vector <string>* description = new vector<string>; // char *description[10];

		string bmpPath;
		ALLEGRO_BITMAP *bmpMain = al_load_bitmap("data//skill//bmp//skillTable.png");

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
			File.close();
		}

		// zaladowac z pliku itemy do listy, brac pod uwage flagi przedmiotow przy tworzeniu nowych obiektów
		// flagi moga byc nie potrzebne dziêki u¿yciu RTTI
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
		al_draw_textf(allegro_font->font12, al_map_rgb(255, 255, 255), 362, 405, ALLEGRO_ALIGN_CENTRE, "Select skill for #%d slot", 0);



	}

};