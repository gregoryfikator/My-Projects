#pragma once
#include "Character.h"
#include "Item.h"
#include "Skill.h"

class Hero :public Character
{
	ALLEGRO_BITMAP *heroPortrait;
	bool heroClass;

	StatsHero *statsHero;

	Item *eq[20];
	Item *eqWorn[7];
	Skill *eqDock[7];

	
public:
	Hero(string newName, bool newHeroClass, string newBMP, int startPointX, int startPointY) : Character(newName, newBMP, startPointX, startPointY)
	{
		for (int i = 0; i < 20; i++)
			eq[i] = nullptr;
		for (int i = 0; i < 7; i++)
			eqDock[i] = nullptr;

		heroClass = newHeroClass;
		if (heroClass)
			heroPortrait = al_load_bitmap("projekt//war.jpg");
		else
			heroPortrait = al_load_bitmap("projekt//wiz.jpg"); 

		statsHero = nullptr;
	}

	ALLEGRO_BITMAP * getPortrait()
	{
		return heroPortrait;
	}

	bool AssignNewItem(Item *newItem)
	{
		for (int i = 0; i < 20; i++)
		{
			if (eq[i] == nullptr)
			{
				eq[i] = newItem;
				return true;
			}
		}		
		return false;
	}

	void DrawItemsFromBackpack()
	{
		int slot = 0;
		int slotX = 71;
		int slotY = 113;

		for (int j = 0; j < 5; j++, slotY += 43, slotX = 71)
		{
			for (int k = 0; k < 4; k++, slot++, slotX += 43)
			{
				if (eq[slot] != nullptr)
				{
					if (eq[slot]->selected)
						al_draw_filled_rounded_rectangle(slotX - 2, slotY - 1, slotX + 43, slotY + 43, 8, 8, al_map_rgb(30, 255, 30));

					al_draw_scaled_bitmap(eq[slot]->bmp, 0, 0, al_get_bitmap_width(eq[slot]->bmp), al_get_bitmap_height(eq[slot]->bmp), slotX, slotY, 42, 42, 0);
				}
			}
		}
	}
};