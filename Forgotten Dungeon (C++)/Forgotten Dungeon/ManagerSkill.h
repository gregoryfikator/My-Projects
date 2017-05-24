#pragma once
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include "Skill.h"

using namespace std;

class ManagerSkill
{
	list<Skill *> *skillList;

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
		vector <string>* description; // char *description[10];

		string bmpPath;
		ALLEGRO_BITMAP *bmpMain = al_load_bitmap("data//skill//bmp//skillTable.png");

		description = new vector<string>;
		fstream File;
		stringstream ss;

		File.open(itemFile.c_str(), ios::in);

		if (File.good())
		{
			skillList = new list<Skill *>;
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
	// Item DropItem(); //metoda losuje przedmiot zdobywany po pokonaniu przeciwnika

};