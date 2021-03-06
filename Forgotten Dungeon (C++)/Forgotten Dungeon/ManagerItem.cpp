#include "ManagerItem.h"

ManagerItem::ManagerItem() : Manager()
{
	itemList = nullptr;
	overlayedItemIndex = -1;
	selectedItemIndex = -1;
	overlayBackpack = false;
	selectedFromBackpack = false;
	selectedItem = nullptr;

	XPBarLength = 0;

	recalculate = false;
}
ManagerItem::~ManagerItem()
{
	for (int i = 0; i < itemList->size(); i++)
	{
		Item* element = itemList->at(i);
		delete element;
	}
	delete itemList;
};
void ManagerItem::Init(string itemFile)
{
	string name;
	vector <string>* description = new vector<string>;
	short int descriptionLines;
	short int descritptionFrameX;
	short int descriptionFrameY;

	short int ID;
	short int flag;
	short int rarity;
	short int lvl;

	float dmg_min;
	float dmg_max;

	unsigned int def;

	float hp;
	float emp;

	int str;
	int dur;
	int dex;
	int agi;
	int wis;
	int chr;

	fstream File;
	stringstream ss;

	File.open(itemFile.c_str(), ios::in);

	if (File.good())
	{
		itemList = new vector<Item *>;
		while (File >> flag >> ID >> lvl >> rarity >> hp >> emp >> str >> dur >> dex >> agi >> wis >> chr >> dmg_min >> dmg_max >> def >> descritptionFrameX >> descriptionLines)
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
			ss << ID;
			tmp = ss.str();
			string bmpPath = "data//item//bmp//" + tmp + ".png";
			ss.str("");

			switch (flag)
			{
			case 1:
				itemList->push_back(new Weapon(flag, ID, lvl, rarity, hp, emp, str, dur, dex, agi, wis, chr, dmg_min, dmg_max, def, descritptionFrameX, descriptionFrameY, descriptionLines, bmpPath, name, description));
				break;
			case 2:
				itemList->push_back(new Shield(flag, ID, lvl, rarity, hp, emp, str, dur, dex, agi, wis, chr, dmg_min, dmg_max, def, descritptionFrameX, descriptionFrameY, descriptionLines, bmpPath, name, description));
				break;
			case 3:
				itemList->push_back(new Helmet(flag, ID, lvl, rarity, hp, emp, str, dur, dex, agi, wis, chr, dmg_min, dmg_max, def, descritptionFrameX, descriptionFrameY, descriptionLines, bmpPath, name, description));
				break;
			case 4:
				itemList->push_back(new ChestArmour(flag, ID, lvl, rarity, hp, emp, str, dur, dex, agi, wis, chr, dmg_min, dmg_max, def, descritptionFrameX, descriptionFrameY, descriptionLines, bmpPath, name, description));
				break;
			case 5:
				itemList->push_back(new LegsArmour(flag, ID, lvl, rarity, hp, emp, str, dur, dex, agi, wis, chr, dmg_min, dmg_max, def, descritptionFrameX, descriptionFrameY, descriptionLines, bmpPath, name, description));
				break;
			case 6:
				itemList->push_back(new Ring(flag, ID, lvl, rarity, hp, emp, str, dur, dex, agi, wis, chr, dmg_min, dmg_max, def, descritptionFrameX, descriptionFrameY, descriptionLines, bmpPath, name, description));
				break;
			default:
				break;
			}
			description = new vector<string>;
		}
		delete description;
		File.close();
	}

	// zaladowac z pliku itemy do listy, brac pod uwage flagi przedmiotow przy tworzeniu nowych obiekt�w
	// flagi moga byc nie potrzebne dzi�ki u�yciu RTTI
}

void ManagerItem::ChangeXPBarLength(int exp, int threshold)
{
	XPBarLength = (int)floor((439 - 282)* exp / threshold);
}

void ManagerItem::Draw(Hero *hero, Resources *resources, ALLEGRO_Font *allegro_font)
{
	// rysowanie ekwipunku
	al_draw_filled_rectangle(0, 0, 720, 480, allegro_font->TRANSPARENT_BLACK3);
	al_draw_bitmap(resources->ui_eq, 30, 43, 0);
	al_draw_filled_rounded_rectangle(282, 341, 282 + XPBarLength, 362, 2, 2, allegro_font->LIGHT_GREEN); //X: 437 //al_draw_filled_rounded_rectangle(282, 341, 282 + x_percent_part, 362, 2, 2, al_map_rgb(45, 210, 55));
	al_draw_bitmap(resources->ui_xp_bar, 259, 305, 0);

	// efekt podswietlenia t�a przedmiotow w ekwipunku - realizowany w metodzie DrawItemsFromBackpack()

	this->DrawItemsFromBackpack(hero);

	// tutaj powinny byc rysowane efekty takie jak przyciemnienie przedmiotow w ekwipunku

	al_draw_bitmap(resources->ui_eq_list, 64, 107, 0);

	//tutaj rysowac podwietlenie zaznaczonego zalozonego przedmiotu

	this->DrawHighlight(hero);

	al_draw_bitmap(resources->ui_eq_wear, 258, 107, 0);

	this->DrawWearingItems(hero);

	if (selectedItemIndex != -1) // docelowo kosz staje sie aktywny i mozna usunac przedmiot gdy zostanie zaznaczony
		al_draw_bitmap(resources->ui_bin, 53, 379, 0);

	al_draw_text(allegro_font->font20, allegro_font->ORANGE, 362, 50, ALLEGRO_ALIGN_CENTRE, "INVENTORY");

	al_draw_textf(allegro_font->font18, allegro_font->LIGHT_YELLOW, 362, 85, ALLEGRO_ALIGN_CENTRE, "%s", hero->GetName().c_str());

	al_draw_text(allegro_font->font20, allegro_font->LIGHT_YELLOW, 640, 120, ALLEGRO_ALIGN_CENTRE, "LEVEL");
	al_draw_textf(allegro_font->font18, allegro_font->WHITE, 640, 145, ALLEGRO_ALIGN_CENTRE, "%d", hero->GetLevel());

	al_draw_text(allegro_font->font18, allegro_font->WHITE, 475, 115, 0, "Health");
	al_draw_textf(allegro_font->font18, allegro_font->LIGHT_GREEN, 573, 115, ALLEGRO_ALIGN_CENTRE, "%.2f", hero->heroStats->hp);
	al_draw_text(allegro_font->font18, allegro_font->WHITE, 475, 135, 0, "Energy");
	al_draw_textf(allegro_font->font18, allegro_font->LIGHT_GREEN, 573, 135, ALLEGRO_ALIGN_CENTRE, "%.2f", hero->heroStats->emp);
	al_draw_text(allegro_font->font18, allegro_font->WHITE, 475, 155, 0, "Armour");
	al_draw_textf(allegro_font->font18, allegro_font->LIGHT_GREEN, 573, 155, ALLEGRO_ALIGN_CENTRE, "%d", hero->heroStats->def);

	al_draw_text(allegro_font->font18, allegro_font->LIGHT_YELLOW, 475, 190, 0, "Stats");
	al_draw_text(allegro_font->font18, allegro_font->LIGHT_YELLOW, 560, 190, 0, "base");
	al_draw_text(allegro_font->font18, allegro_font->LIGHT_YELLOW, 602, 190, 0, "current");

	al_draw_text(allegro_font->font18, allegro_font->WHITE, 475, 210, 0, "Strength");
	al_draw_textf(allegro_font->font18, allegro_font->WHITE, 576, 210, ALLEGRO_ALIGN_CENTRE, "%d", hero->heroStats->str);
	this->DrawCurrentStats(633, 210, hero->heroStats->str, hero->heroStats->str_eq, allegro_font);

	al_draw_text(allegro_font->font18, allegro_font->WHITE, 475, 230, 0, "Durability");
	al_draw_textf(allegro_font->font18, allegro_font->WHITE, 576, 230, ALLEGRO_ALIGN_CENTRE, "%d", hero->heroStats->dur);
	this->DrawCurrentStats(633, 230, hero->heroStats->dur, hero->heroStats->dur_eq, allegro_font);

	al_draw_text(allegro_font->font18, allegro_font->WHITE, 475, 250, 0, "Dexterity");
	al_draw_textf(allegro_font->font18, allegro_font->WHITE, 576, 250, ALLEGRO_ALIGN_CENTRE, "%d", hero->heroStats->dex);
	this->DrawCurrentStats(633, 250, hero->heroStats->dex, hero->heroStats->dex_eq, allegro_font);

	al_draw_text(allegro_font->font18, allegro_font->WHITE, 475, 270, 0, "Agility");
	al_draw_textf(allegro_font->font18, allegro_font->WHITE, 576, 270, ALLEGRO_ALIGN_CENTRE, "%d", hero->heroStats->agi);
	this->DrawCurrentStats(633, 270, hero->heroStats->agi, hero->heroStats->agi_eq, allegro_font);

	al_draw_text(allegro_font->font18, allegro_font->WHITE, 475, 290, 0, "Wisdom");
	al_draw_textf(allegro_font->font18, allegro_font->WHITE, 576, 290, ALLEGRO_ALIGN_CENTRE, "%d", hero->heroStats->wis);
	this->DrawCurrentStats(633, 290, hero->heroStats->wis, hero->heroStats->wis_eq, allegro_font);

	al_draw_text(allegro_font->font18, allegro_font->WHITE, 475, 310, 0, "Charisma");
	al_draw_textf(allegro_font->font18, allegro_font->WHITE, 576, 310, ALLEGRO_ALIGN_CENTRE, "%d", hero->heroStats->chr);
	this->DrawCurrentStats(633, 310, hero->heroStats->chr, hero->heroStats->chr_eq, allegro_font);
}
void ManagerItem::DrawCurrentStats(int X, int Y, int baseStat, int currentStat, ALLEGRO_Font *fonts)
{
	if (baseStat < currentStat)
		al_draw_textf(fonts->font18, fonts->LIGHT_GREEN, X, Y, ALLEGRO_ALIGN_CENTRE, "%d", currentStat);
	else if (baseStat > currentStat)
		al_draw_textf(fonts->font18, fonts->DARK_RED, X, Y, ALLEGRO_ALIGN_CENTRE, "%d", currentStat);
	else
		al_draw_textf(fonts->font18, fonts->WHITE, X, Y, ALLEGRO_ALIGN_CENTRE, "%d", currentStat);
}
void ManagerItem::DrawItemsFromBackpack(Hero *hero)
{
	int slot = 0;
	int slotX = 71;
	int slotY = 113;

	for (int j = 0; j < 5; j++, slotY += 43, slotX = 71)
		for (int k = 0; k < 4; k++, slot++, slotX += 43)
			if (hero->eq[slot] != nullptr)
			{
				if (hero->eq[slot]->selected)
					al_draw_filled_rounded_rectangle(slotX - 2, slotY - 1, slotX + 43, slotY + 43, 8, 8, al_map_rgb(30, 255, 30));

				al_draw_scaled_bitmap(hero->eq[slot]->bmp, 0, 0, al_get_bitmap_width(hero->eq[slot]->bmp), al_get_bitmap_height(hero->eq[slot]->bmp), slotX, slotY, 42, 42, 0);
			}
}
void ManagerItem::DrawWearingItems(Hero *hero)
{
	if (hero->eqWorn[0] != nullptr)
		al_draw_tinted_scaled_rotated_bitmap_region(hero->eqWorn[0]->bmp, al_get_bitmap_width(hero->eqWorn[0]->bmp) / 4, 0, al_get_bitmap_width(hero->eqWorn[0]->bmp) * 3 / 4, al_get_bitmap_height(hero->eqWorn[0]->bmp), al_map_rgba_f(1, 1, 1, 1), 0, 0, 284, 173, 0.50, 0.42, 0, 0); //0.58666, 0.46, 0, 0);
	if (hero->eqWorn[1] != nullptr)
		al_draw_tinted_scaled_rotated_bitmap_region(hero->eqWorn[1]->bmp, 0, 0, al_get_bitmap_width(hero->eqWorn[1]->bmp), al_get_bitmap_height(hero->eqWorn[1]->bmp), al_map_rgba_f(1, 1, 1, 1), 0, 0, 386, 173, 0.5, 0.5, 0, 0);
	if (hero->eqWorn[2] != nullptr)
		al_draw_tinted_scaled_rotated_bitmap_region(hero->eqWorn[2]->bmp, 0, 0, al_get_bitmap_width(hero->eqWorn[2]->bmp), al_get_bitmap_height(hero->eqWorn[2]->bmp), al_map_rgba_f(1, 1, 1, 1), 0, 0, 340, 126, 0.66, 0.66, 0, 0);
	if (hero->eqWorn[3] != nullptr)
		al_draw_tinted_scaled_rotated_bitmap_region(hero->eqWorn[3]->bmp, 0, 0, al_get_bitmap_width(hero->eqWorn[3]->bmp), al_get_bitmap_height(hero->eqWorn[3]->bmp), al_map_rgba_f(1, 1, 1, 1), 0, 0, 335, 180, 0.72, 0.75, 0, 0);
	if (hero->eqWorn[4] != nullptr)
		al_draw_tinted_scaled_rotated_bitmap_region(hero->eqWorn[4]->bmp, 0, 0, al_get_bitmap_width(hero->eqWorn[4]->bmp), al_get_bitmap_height(hero->eqWorn[4]->bmp), al_map_rgba_f(1, 1, 1, 1), 0, 0, 323, 252, 0.6, 0.55, 0, 0);
	if (hero->eqWorn[5] != nullptr)
		al_draw_tinted_scaled_rotated_bitmap_region(hero->eqWorn[5]->bmp, 0, 0, al_get_bitmap_width(hero->eqWorn[5]->bmp), al_get_bitmap_height(hero->eqWorn[5]->bmp), al_map_rgba_f(1, 1, 1, 1), 0, 0, 295, 255, 0.43, 0.43, 0, 0);
	if (hero->eqWorn[6] != nullptr)
		al_draw_tinted_scaled_rotated_bitmap_region(hero->eqWorn[6]->bmp, 0, 0, al_get_bitmap_width(hero->eqWorn[6]->bmp), al_get_bitmap_height(hero->eqWorn[6]->bmp), al_map_rgba_f(1, 1, 1, 1), 0, 0, 396, 255, 0.43, 0.43, 0, 0);
}
void ManagerItem::DrawHighlight(Hero *hero)
{
	for (int i = 0; i < 7; i++)
	{
		if (hero->eqWorn[i] != nullptr)
		{
			switch (i)
			{
			case 0:
				if (hero->eqWorn[i]->selected)
					al_draw_filled_rounded_rectangle(280, 166, 324, 240, 8, 8, al_map_rgb(30, 255, 30));
				break;
			case 1:
				if (hero->eqWorn[i]->selected)
					al_draw_filled_rounded_rectangle(393, 166, 439, 240, 8, 8, al_map_rgb(30, 255, 30));
				break;
			case 2:
				if (hero->eqWorn[i]->selected)
					al_draw_filled_rounded_rectangle(335, 122, 381, 167, 8, 8, al_map_rgb(30, 255, 30));
				break;
			case 3:
				if (hero->eqWorn[i]->selected)
					al_draw_filled_rounded_rectangle(335, 175, 381, 245, 8, 8, al_map_rgb(30, 255, 30));
				break;
			case 4:
				if (hero->eqWorn[i]->selected)
					al_draw_filled_rounded_rectangle(335, 253, 381, 317, 8, 8, al_map_rgb(30, 255, 30));
				break;
			case 5:
				if (hero->eqWorn[i]->selected)
					al_draw_filled_rounded_rectangle(292, 248, 324, 284, 8, 8, al_map_rgb(30, 255, 30));
				break;
			case 6:
				if (hero->eqWorn[i]->selected)
					al_draw_filled_rounded_rectangle(393, 248, 426, 284, 8, 8, al_map_rgb(30, 255, 30));
				break;
			default:
				break;
			}
		}
	}
}
bool ManagerItem::CheckButtons(int mouseX, int mouseY, Hero *hero, bool LMBPressed)
{
	if (LMBPressed)
	{
		if (mouseX >= 54 && mouseX <= 80 && mouseY <= 407 && mouseY >= 380)
		{
			if (selectedItemIndex != -1)
			{
				if (selectedFromBackpack)
				{
					delete hero->eq[selectedItemIndex];
					hero->eq[selectedItemIndex] = nullptr;
					selectedFromBackpack = false;
				}
				else
				{
					delete hero->eqWorn[selectedItemIndex];
					hero->eqWorn[selectedItemIndex] = nullptr;
					recalculate = true;
				}
				selectedItemIndex = -1;
				selectedItem = nullptr;
			}
		}

		if (mouseX >= 638 && mouseX <= 664 && mouseY >= 380 && mouseY <= 407)
		{
			if (selectedFromBackpack == true && hero->eq[selectedItemIndex] != nullptr)
				hero->eq[selectedItemIndex]->selected = false;
			else if (hero->eqWorn[selectedItemIndex] != nullptr)
				hero->eqWorn[selectedItemIndex]->selected = false;

			selectedItemIndex = -1;
			selectedFromBackpack = false;
			selectedItem = nullptr;
			return false;
		}
	}
	return true;
}
void ManagerItem::CheckCursorOverlayBackpackAndClick(int mouseX, int mouseY, Hero *hero, bool LMBPressed) // funkcja jest 'nieelegancko' wykonana ze wzgledu na ograniczenia czasowe
{
	int x1eq = 71;
	int y1eq = 113;
	if (mouseX >= x1eq && mouseX < x1eq + 4 * 43 && mouseY >= y1eq && mouseY < y1eq + 5 * 43)	// sprawdzenie czy kursor znajduje sie w polu ekwipunku
	{
		overlayBackpack = true;
		for (int i = 0; i < 20; y1eq += 43, x1eq = 71)	// itereacja po rzedach
			for (int j = 0; j < 4; j++, i++, x1eq += 43) //iteracja po kolumnach
			{
				if (mouseX >= x1eq && mouseX < x1eq + 43 && mouseY >= y1eq && mouseY < y1eq + 43) // sprawdzenie komorki w rzedzie
				{
					if (hero->eq[i] != nullptr)
					{
						overlayedItemIndex = i;

						if (LMBPressed)
						{
							if (selectedItem == nullptr)
							{
								selectedItemIndex = i;
								selectedFromBackpack = true;
								selectedItem = hero->eq[i];
								selectedItem->selected = true;
							}
							else if (selectedItem == hero->eq[i])
							{
								selectedItemIndex = -1;
								selectedFromBackpack = false;
								selectedItem->selected = false;
								selectedItem = nullptr;
							}
							else if (selectedItem != nullptr && selectedItem != hero->eq[i])
							{
								if (selectedFromBackpack)
								{
									hero->SwapItems(selectedItem, hero->eq[i], i, selectedItemIndex);
									selectedItem = nullptr;
									hero->eq[i]->selected = false;
									selectedItemIndex = -1;
									selectedFromBackpack = false;
									recalculate = true;
								}
								else if (typeid(*selectedItem->original).name() == typeid(*hero->eq[i]->original).name())
								{
									hero->SwapItems(selectedItem, hero->eq[i], i, selectedItemIndex, selectedFromBackpack);
									selectedItem = nullptr;
									hero->eq[i]->selected = false;
									selectedItemIndex = -1;
									recalculate = true;
									selectedFromBackpack = false;
								}
							}

						}
						return;
					}
					if (selectedItem != nullptr && LMBPressed)
					{
						if (selectedFromBackpack == true)
							hero->SwapItems(selectedItem, hero->eq[i], i, selectedItemIndex);
						else
							hero->SwapItems(selectedItem, hero->eq[i], i, selectedItemIndex, selectedFromBackpack);

						selectedItem = nullptr;
						hero->GetItemFromBackpack(i)->selected = false;
						selectedItemIndex = -1;
						selectedFromBackpack = false;
						recalculate = true;
						return;
					}
				}
			}
	}
	// jesli kursor znajdzie sie poza polem ekwipunku
	overlayedItemIndex = -1;
	overlayBackpack = false;
}
void ManagerItem::CheckCursorOverlayWearingAndClick(int mouseX, int mouseY, Hero *hero, bool LMBPressed) // funkcja jest 'nieelegancko' wykonana ze wzgledu na ograniczenia czasowe
{
	if (mouseX >= 280 && mouseY >= 122 && mouseX <= 439 && mouseY <= 317)
	{
		//LEWA KOLUMNA
		if (mouseX <= 324)
		{
			//LEWA REKA
			if (mouseY >= 166 && mouseY <= 240)
			{
				ProceedItemChange(hero, LMBPressed, 0, "class Weapon");
				return;
			}
			if (mouseY >= 248 && mouseY <= 284)
			{
				ProceedItemChange(hero, LMBPressed, 5, "class Ring");
			}
		}
		//SRODKOWA KOLUMNA
		else if (mouseX >= 335 && mouseX <= 381)
		{
			//GLOWA
			if (mouseY <= 167)
			{
				ProceedItemChange(hero, LMBPressed, 2, "class Helmet");
				return;
			}
			//ZBROJA
			if (mouseY >= 175 && mouseY <= 245)
			{
				ProceedItemChange(hero, LMBPressed, 3, "class ChestArmour");
				return;
			}
			//NOGI
			if (mouseY >= 253 && mouseY <= 317)
			{
				ProceedItemChange(hero, LMBPressed, 4, "class LegsArmour");
			}
		}
		//PRAWA KOLUMNA
		else if (mouseX >= 393)
		{
			//PRAWA REKA
			if (mouseY >= 166 && mouseY <= 240)
			{
				ProceedItemChange(hero, LMBPressed, 1, "class Shield");
				return;
			}
			//PRAWY PIERSCIEN
			if (mouseY >= 248 && mouseY <= 284)
			{
				ProceedItemChange(hero, LMBPressed, 6, "class Ring");
			}
		}
	}
}
void ManagerItem::ProceedItemChange(Hero *hero, bool LMBPressed, int slot, const char *type)
{
	if (hero->eqWorn[slot] != nullptr)
	{
		overlayedItemIndex = slot;
		if (LMBPressed)
		{
			if (selectedItem == nullptr)
			{
				selectedItemIndex = slot;
				selectedItem = hero->eqWorn[slot];
				selectedItem->selected = true;
			}
			else if (selectedItem == hero->eqWorn[slot])
			{
				selectedItemIndex = -1;
				selectedItem->selected = false;
				selectedItem = nullptr;
			}
			else
			{
				if (typeid(*selectedItem->original).name() == typeid(*hero->eqWorn[slot]->original).name())
				{
					if (selectedFromBackpack == true)
						hero->SwapItems(selectedItem, hero->eqWorn[slot], slot, selectedItemIndex, selectedFromBackpack);
					else if (slot == 6 && selectedItemIndex == slot - 1 || slot == 5 && selectedItemIndex == slot + 1)
						hero->SwapItems2(selectedItem, hero->eqWorn[slot], slot, selectedItemIndex);

					selectedItem = nullptr;
					selectedItemIndex = -1;
					selectedFromBackpack = false;
					hero->eqWorn[slot]->selected = false;
					recalculate = true;
				}
			}
			return;
		}
	}
	if (selectedItem != nullptr && LMBPressed)
	{
		if (strcmp(typeid(*selectedItem->original).name(), type) == 0)
		{
			if (slot == 6 && selectedItemIndex == slot - 1 || slot == 5 && selectedItemIndex == slot + 1)
				hero->SwapItems2(selectedItem, hero->eqWorn[slot], slot, selectedItemIndex);
			else
				hero->SwapWithEmpty(selectedItem, slot, selectedItemIndex, true);
			hero->eqWorn[slot]->selected = false;
			selectedItem = nullptr;
			selectedItemIndex = -1;
			selectedFromBackpack = false;
			recalculate = true;
		}
		//else play deny sound
	}
}
void ManagerItem::RecalculateStats(Hero *hero)
{
	hero->heroStats->str_eq = hero->heroStats->str;
	hero->heroStats->dur_eq = hero->heroStats->dur;
	hero->heroStats->agi_eq = hero->heroStats->agi;
	hero->heroStats->dex_eq = hero->heroStats->dex;
	hero->heroStats->wis_eq = hero->heroStats->wis;
	hero->heroStats->chr_eq = hero->heroStats->chr;

	hero->heroStats->def = 0;
	hero->heroStats->dmg_min = 0;
	hero->heroStats->dmg_max = 2;

	if (hero->heroClass)
	{
		hero->heroStats->hp = 50;
		hero->heroStats->emp = 25;

	}
	else
	{
		hero->heroStats->hp = 30;
		hero->heroStats->emp = 50;
	}
	for (int i = 0; i < 7; i++)
	{
		if (hero->eqWorn[i] != nullptr)
		{
			hero->heroStats->str_eq += hero->eqWorn[i]->stats->str;
			hero->heroStats->dur_eq += hero->eqWorn[i]->stats->dur;
			hero->heroStats->agi_eq += hero->eqWorn[i]->stats->agi;
			hero->heroStats->dex_eq += hero->eqWorn[i]->stats->dex;
			hero->heroStats->wis_eq += hero->eqWorn[i]->stats->wis;
			hero->heroStats->chr_eq += hero->eqWorn[i]->stats->chr;

			hero->heroStats->def += hero->eqWorn[i]->stats->def;
			hero->heroStats->dmg_min += hero->eqWorn[i]->stats->dmg_min;
			hero->heroStats->dmg_max += hero->eqWorn[i]->stats->dmg_max;

			hero->heroStats->hp += hero->eqWorn[i]->stats->hp;
			hero->heroStats->emp += hero->eqWorn[i]->stats->emp;
		}
	}
	recalculate = false;
}

int ManagerItem::GetOverlayedItemIndex() { return overlayedItemIndex; }
bool ManagerItem::GetOverlayBackpack() { return overlayBackpack; }
bool ManagerItem::CheckRecalculation() { return recalculate; }

void ManagerItem::DrawDescription(int mouseX, int mouseY, Item *item, ALLEGRO_Font *fonts, int y)
{
	if (item != nullptr)
	{
		al_draw_filled_rounded_rectangle(mouseX, mouseY - item->descriptionFrameY, mouseX + item->descriptionFrameX, mouseY, 8, 8, fonts->TRANSPARENT_BLACK5);
		al_draw_rounded_rectangle(mouseX, mouseY - item->descriptionFrameY, mouseX + item->descriptionFrameX, mouseY, 8, 8, fonts->TRANSPARENT_BLACK6, 2.5);
		al_draw_textf(fonts->font20, fonts->LIGHT_YELLOW, mouseX + item->descriptionFrameX / 2, mouseY + 5 - item->descriptionFrameY, ALLEGRO_ALIGN_CENTRE, "%s", item->name.c_str());

		for (int i = 0; i < item->description.size(); i++)
		{
			al_draw_textf(fonts->font12, fonts->WHITE, mouseX + item->descriptionFrameX / 2, mouseY + y - item->descriptionFrameY, ALLEGRO_ALIGN_CENTRE, item->description[i].c_str());
			y += 16;
		}
	}
}

Item ManagerItem::DropItem(bool startingItem) //metoda losuje przedmiot zdobywany po pokonaniu przeciwnika
{
	if (startingItem == true)
		return *itemList->at(1);

	int stop = rand() % itemList->size();
	return *itemList->at(stop);
}