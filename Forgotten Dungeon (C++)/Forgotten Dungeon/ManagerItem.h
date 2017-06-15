#pragma once
#define CRT_SECURE_NO_WARNINGS

#include <allegro5/allegro_primitives.h>
#include <vector>
#include <typeinfo>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "Manager.h"
#include "ItemTypes.h"
#include "Hero.h"
#include "Resources.h"
#include "ALLEGRO_Font.h"

class ManagerItem : public Manager
{
	vector<Item *> *itemList;
	int overlayedItemIndex;
	int selectedItemIndex;
	bool overlayBackpack;
	bool selectedFromBackpack;

	bool recalculate;

	Item *selectedItem;

	int XPBarLength;

public:
	ManagerItem();
	~ManagerItem();
	virtual void Init(string itemFile = "data//item//itemlist.txt");

	void ChangeXPBarLength(int exp, int threshold);

	void Draw(Hero *hero, Resources *resources, ALLEGRO_Font *allegro_font);
	static void DrawCurrentStats(int X, int Y, int baseStat, int currentStat, ALLEGRO_Font *fonts);
	static void DrawItemsFromBackpack(Hero *hero);
	static void DrawWearingItems(Hero *hero);
	static void DrawHighlight(Hero *hero);
	bool CheckButtons(int mouseX, int mouseY, Hero *hero, bool LMBPressed);
	void CheckCursorOverlayBackpackAndClick(int mouseX, int mouseY, Hero *hero, bool LMBPressed); // funkcja jest 'nieelegancko' wykonana ze wzgledu na ograniczenia czasowe

	void CheckCursorOverlayWearingAndClick(int mouseX, int mouseY, Hero *hero, bool LMBPressed); // funkcja jest 'nieelegancko' wykonana ze wzgledu na ograniczenia czasowe

	void ProceedItemChange(Hero *hero, bool LMBPressed, int slot, const char *type);
	void RecalculateStats(Hero *hero);

	int GetOverlayedItemIndex();
	bool GetOverlayBackpack();
	bool CheckRecalculation();

	static void DrawDescription(int mouseX, int mouseY, Item *item, ALLEGRO_Font *fonts, int y = 34);
	Item DropItem(bool startingItem = false); //metoda losuje przedmiot zdobywany po pokonaniu przeciwnika
};