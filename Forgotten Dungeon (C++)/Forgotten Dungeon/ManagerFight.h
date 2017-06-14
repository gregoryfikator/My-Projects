#pragma once

#include "Manager.h"
#include "Hero.h"
#include "Enemy.h"
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
	ManagerFight() : Manager()
	{
		hero = nullptr;
		enemy = nullptr;

		fightLog = new list<string>;
		
		heroHR = 0;
		enemyHR = 0;

		round = 0;
		fightFinished = false;

		MouseX = MouseY = 0;

		usedSkill = -1;
		bleedingDuration = 0;
	}
	~ManagerFight()
	{
		if (fightLog != nullptr)
		{
			while (!fightLog->empty())
				fightLog->pop_front();
			delete fightLog;
		}
	}

	void Init(Hero *hero_, Enemy *enemy_)
	{
		hero = hero_;
		enemy = enemy_;	
		fightLog->clear();

		heroHP = hero->heroStats->hp;
		heroEMP = hero->heroStats->emp;

		enemyHP = enemy->stats->hp;

		round = 0;
		fightFinished = false;

		usedSkill = -1;	
		bleedingDuration = 0;

		this->HitRatio();

	}

	void EndFight()
	{
		while (!fightLog->empty())
			fightLog->pop_front();
	}

	void HitRatio()
	{
		double HRIndicator = (0.6 * (hero->GetLevel() - enemy->GetLevel()) + 0.4 * (hero->heroStats->dex_eq - enemy->stats->agi)) / 24;
		this->CompareIndicator(HRIndicator, &heroHR);

		HRIndicator = (0.6 * (enemy->GetLevel() - hero->GetLevel()) + 0.4 * (enemy->stats->dex - hero->heroStats->agi_eq)) / 24;
		this->CompareIndicator(HRIndicator, &enemyHR);
	}

	void CompareIndicator(double HRIndicator, double *calculatedHR)
	{
		if (HRIndicator < 0)
		{
			*calculatedHR = exp(HRIndicator);
			*calculatedHR = 80 * *calculatedHR;
			if (*calculatedHR < 33)
				*calculatedHR = 33;
		}
		else if (HRIndicator > 0)
		{
			*calculatedHR = 1 - exp(-HRIndicator);
			*calculatedHR = 80 + 20 * *calculatedHR;
			if (*calculatedHR > 95)
				*calculatedHR = 95;
		}
		else
			*calculatedHR = 80;
	}

	bool Fight()
	{	
		if (usedSkill != -1)
		{			
			if (hero->GetDockedSkill(usedSkill) != nullptr)
			{
				round++;			

				fightLog->push_back("Round #" + to_string(round));
				fightLog->push_back(hero->GetName() + " used '" + hero->GetDockedSkill(usedSkill)->name + "' and...");

				if (hero->GetDockedSkill(usedSkill)->flag == 0) // uzycie mikstury
				{
					if (hero->GetDockedSkill(usedSkill)->quantity > 0)
					{
						if (hero->GetDockedSkill(usedSkill)->stats->hp > 0)
						{
							fightLog->push_back("regenerated " + to_string(hero->GetDockedSkill(usedSkill)->stats->hp) + " points of health!");
							heroHP += hero->GetDockedSkill(usedSkill)->stats->hp;
							if (heroHP > hero->heroStats->hp)
								heroHP = hero->heroStats->hp;
						}
						else
						{
							fightLog->push_back("regenerated " + to_string(hero->GetDockedSkill(usedSkill)->stats->emp) + " points of energy!");
							heroEMP += hero->GetDockedSkill(usedSkill)->stats->emp;
							if (heroEMP > hero->heroStats->emp)
								heroEMP = hero->heroStats->emp;
						}
						hero->GetDockedSkill(usedSkill)->quantity--;
					}
					else
						fightLog->push_back("failed! Hero has no more potions!");
				}
				else if (hero->GetDockedSkill(usedSkill)->flag == 10) // uzycie umiejetnosci do ataku
				{
					if (hero->GetDockedSkill(usedSkill)->currentCooldown == 0)
					{
						this->DecrementCooldowns();

						if (heroEMP + hero->GetDockedSkill(usedSkill)->stats->emp >= 0)
						{
							heroEMP += hero->GetDockedSkill(usedSkill)->stats->emp;
							if (1 + rand() % 100 < heroHR || hero->GetDockedSkill(usedSkill)->stats->unblockable == true)
							{					
								double dmgGiven = (hero->heroStats->dmg_max - hero->heroStats->dmg_min) * (1 + rand() % 100) / 100 + hero->heroStats->dmg_min;
								double dmgReduction = dmgGiven * enemy->stats->def / (100 + 25 * (enemy->GetLevel() - 1));
								dmgGiven -= dmgReduction;
								dmgGiven = dmgGiven + dmgGiven * hero->GetDockedSkill(usedSkill)->stats->dmgGivenMultipler;
								if (dmgGiven < 0)
									dmgGiven = 0;
								enemyHP = enemyHP - dmgGiven;
							
								stringstream ss;
								ss << fixed;
								ss.precision(2); // set 2 places after coma
								ss << dmgGiven;

								if (bleedingDuration > 0) // efekt krwawienia -1 hp/runde
								{
									bleedingDuration--;
									enemyHP--;
									fightLog->push_back("hit! Enemy has losed " + ss.str() + " HP + 1 HP for bleeding!");
								}
								else
									fightLog->push_back("hit! Enemy has losed " + ss.str() + "!");	

								if (hero->GetDockedSkill(usedSkill)->stats->bleedingDuration > 0)
								{
									if (1 + rand() % 100 < hero->GetDockedSkill(usedSkill)->stats->bleedingChance * 100)
										bleedingDuration += hero->GetDockedSkill(usedSkill)->stats->bleedingDuration;
								}
							}
							else
								fightLog->push_back("missed! Enemy has blocked attack!");
						}
						else
							fightLog->push_back("failed! Hero was out of energy!");

						hero->GetDockedSkill(usedSkill)->currentCooldown = hero->GetDockedSkill(usedSkill)->cooldown;
					}
					else
						fightLog->push_back("failed! Skill was not ready yet!");
				}
				else if (hero->GetDockedSkill(usedSkill)->flag == 13) // proba ucieczki z walki
				{
					// OBLICZENIE SZANSY NA UCIECZKE (domyslne 75%)
					if (heroEMP + hero->GetDockedSkill(usedSkill)->stats->emp >= 0)
					{
						heroEMP += hero->GetDockedSkill(usedSkill)->stats->emp;
						if (1 + rand() % 101 < 75 + (heroHP / hero->heroStats->hp - enemyHP / enemy->stats->hp))
						{
							escaped = true;
							fightLog->push_back("escaped! Enemy could not catch you!");
						}
						else
							fightLog->push_back("failed! Enemy has chased you!");
					}
				}

				// atak przeciwnika
				fightLog->push_back(enemy->GetName() + " attacked and...");
				if (1 + rand() % 100 < enemyHR)
				{
					double dmgGiven = (enemy->stats->dmg_max - enemy->stats->dmg_min) * (1 + rand() % 100) / 100 + enemy->stats->dmg_min;
					double dmgReduction = dmgGiven * hero->heroStats->def / (100 + 25 * (hero->GetLevel() - 1));
					dmgGiven -= dmgReduction;
					if (dmgGiven < 0)
						dmgGiven = 0;
					heroHP = heroHP - dmgGiven;

					stringstream ss;
					ss << fixed;
					ss.precision(2); // set 2 places after coma
					ss << dmgGiven;

					fightLog->push_back("hit! Your hero has losed " + ss.str() + " HP!");
				}
				else
					fightLog->push_back("missed! Your hero has blocked attack!");
			}
		}
					
		if (heroHP <= 0)
		{
			fightFinished = true;
			return false;
		}
		if (enemyHP <= 0)
		{
			fightFinished = true;
			return true;
		}
		if (escaped == true)
		{
			fightFinished = true;
			return true;
		}

		usedSkill = -1;
		return false;
	}

	void SetUsedSkill(int index) { usedSkill = index; }
	bool GetFightStatus() { return fightFinished; }
	bool CheckIfHeroEscaped() { return escaped; }
	void ResetHeroEscaped() { escaped = false; }

	void DecrementCooldowns()
	{
		for (int i = 0; i < 6; i++)
			if (hero->GetDockedSkill(i) != nullptr)
				if (hero->GetDockedSkill(i)->currentCooldown > 0)
					hero->GetDockedSkill(i)->currentCooldown -= 1;
	}

	void Draw(Resources *resources, ALLEGRO_Font *allegro_font)
	{
		// rysowanie okna walki
		al_draw_bitmap(resources->background, 0, 0, 0);

		al_draw_filled_rounded_rectangle(40, 35, 200, 410, 8, 8, allegro_font->TRANSPARENT_BLACK4);
		al_draw_rounded_rectangle(40, 35, 200, 410, 8, 8, allegro_font->TRANSPARENT_BLACK5, 2.5);

		al_draw_textf(allegro_font->font12, allegro_font->WHITE, 120, 40, ALLEGRO_ALIGN_CENTER, "%s", hero->GetName().c_str());
		al_draw_bitmap_region(hero->GetBMP(), 32, 0, 32, 32, 104, 60, 0);
		al_draw_textf(allegro_font->font14, allegro_font->WHITE, 120, 100, ALLEGRO_ALIGN_CENTER, "Level: %d", hero->GetLevel());
		al_draw_textf(allegro_font->font14, allegro_font->WHITE, 60, 130, 0, "Life: %.2f/%.2f", heroHP, hero->heroStats->hp);
		al_draw_textf(allegro_font->font14, allegro_font->WHITE, 60, 150, 0, "Energy: %.2f/%.2f", heroEMP, hero->heroStats->emp);
		al_draw_textf(allegro_font->font14, allegro_font->WHITE, 60, 170, 0, "Hit chance: %.0f%%", heroHR);

		al_draw_filled_rounded_rectangle(240, 35, 480, 410, 8, 8, allegro_font->TRANSPARENT_BLACK4);
		al_draw_rounded_rectangle(240, 35, 480, 410, 8, 8, allegro_font->TRANSPARENT_BLACK5, 2.5);

		al_draw_filled_rounded_rectangle(520, 35, 680, 410, 8, 8, allegro_font->TRANSPARENT_BLACK4);
		al_draw_rounded_rectangle(520, 35, 680, 410, 8, 8, allegro_font->TRANSPARENT_BLACK5, 2.5);

		al_draw_textf(allegro_font->font12, allegro_font->WHITE, 600, 40, ALLEGRO_ALIGN_CENTER, "%s", enemy->GetName().c_str());
		al_draw_bitmap(enemy->GetBMP(), 584, 60, 0);
		al_draw_textf(allegro_font->font14, allegro_font->WHITE, 600, 100, ALLEGRO_ALIGN_CENTER, "Level: %d", enemy->GetLevel());
		al_draw_textf(allegro_font->font14, allegro_font->WHITE, 540, 130, 0, "Life: %.2f/%.2f", enemyHP, enemy->stats->hp);
		al_draw_textf(allegro_font->font14, allegro_font->WHITE, 540, 170, 0, "Hit chance: %.0f%%", enemyHR);

		al_draw_text(allegro_font->font20, allegro_font->WHITE, 360, 40, ALLEGRO_ALIGN_CENTER, "FIGHT!");
		list<string>::iterator it1;
		for (DrawTextPosY = 70, it1 = fightLog->begin(); it1 != fightLog->end(); ++it1, DrawTextPosY += 20)
		{
			if (DrawTextPosY > 400)
			{
				fightLog->pop_front();
				fightLog->pop_front();
				fightLog->pop_front();
				fightLog->pop_front();
				fightLog->pop_front();
				break;
			}
			al_draw_text(allegro_font->font10, allegro_font->WHITE, 260, DrawTextPosY, 0, (*it1).c_str());		
		}

	}

};