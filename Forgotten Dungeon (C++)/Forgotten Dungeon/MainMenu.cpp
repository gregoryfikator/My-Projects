#include "MainMenu.h"
using namespace std;

MainMenu::MainMenu(ALLEGRO_EVENT_QUEUE *event_queue_new, ALLEGRO_Font *allegro_font_new, ALLEGRO_BITMAP *background_, ALLEGRO_BITMAP *cursor_, ALLEGRO_BITMAP *heroWarrior_, ALLEGRO_BITMAP *heroWizzard_)
{
	event_queue		= event_queue_new;
	allegro_font	= allegro_font_new;

	background		= al_load_bitmap("data//textures//menu.png");
	cursor			= al_load_bitmap("data//textures//cursor.png");
	heroWarrior		= al_load_bitmap("data//textures//war.jpg");
	heroWizard		= al_load_bitmap("data//textures//wiz.jpg");
	characterName	= "Default";

	mouseX			= 0;
	mouseY			= 0;

	mouseOnButton	= false;
	warriorSelected	= false;
	popupMenu		= false;
	NAME_EDIT		= false;

	buttonPanelX1	= 252;
	buttonPanelY1	= 133;
	buttonPanelX2	= 468;
	buttonPanelY2	= 413;

	mainMenuButton[0] = new Button(buttonPanelX1, 181, buttonPanelX2, 221, false, false, "Save Game");
	mainMenuButton[1] = new Button(buttonPanelX1, 133, buttonPanelX2, 173, true, false, "New Game");
	mainMenuButton[2] = new Button(buttonPanelX1, 229, buttonPanelX2, 269, true, false, "Load Game");
	mainMenuButton[3] = new Button(buttonPanelX1, 277, buttonPanelX2, 317, true, false, "Options");
	mainMenuButton[4] = new Button(buttonPanelX1, 325, buttonPanelX2, 365, true, false, "Credits");
	mainMenuButton[5] = new Button(buttonPanelX1, 373, buttonPanelX2, 413, true, false, "Quit");
}

void MainMenu::DrawMenu()
{
	// BACKGROUND
	al_draw_bitmap(background, 0, 0, 0);

	al_draw_filled_rounded_rectangle(90, 12, 630, 468, 8, 8, al_map_rgba(0, 0, 0, 75));
	al_draw_rounded_rectangle(90, 12, 630, 468, 8, 8, al_map_rgba(0, 0, 0, 175), 2.5);

	// HEADER
	al_draw_filled_rounded_rectangle(180, 30, 540, 115, 8, 8, al_map_rgba(0, 0, 0, 125));
	al_draw_rounded_rectangle(180, 30, 540, 115, 8, 8, al_map_rgba(0, 0, 0, 150), 2);

	// HEADER-TEXT
	offSet = al_get_font_line_height(allegro_font->font40);
	al_draw_text(allegro_font->font40, allegro_font->DARK_RED, 360, ((115 + 30 - offSet) / 2), ALLEGRO_ALIGN_CENTRE, "Forgotten Dungeon");
}

void MainMenu::DrawMainMenu()
{
	DrawMenu();
	
	// BUTTONS

	offSet = al_get_font_line_height(allegro_font->font18);
	mainMenuButton[0]->DrawButton(allegro_font, offSet, al_map_rgba(0, 0, 0, 150), 8, 1.5);
	for (int i = 1; i < 6; i++)
		mainMenuButton[i]->DrawButton(allegro_font, offSet, al_map_rgba(0, 0, 0, 125), 8, 1.5);

	al_draw_bitmap(cursor, mouseX, mouseY, 0);

	al_flip_display(); // wyœwietlenie aktualnego bufora na ekran
	al_clear_to_color(al_map_rgb(0, 0, 0)); // wyczyszczenie aktualnego bufora ekranu
}

void MainMenu::GetEvents()
{
	al_wait_for_event(event_queue, &ev);
	if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		mouseX = ev.mouse.x;
		mouseY = ev.mouse.y;
	}

	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		mouseButtonPressedID = ev.mouse.button;

	if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		keyboardKeyPressedID = ev.keyboard.keycode;
}

int MainMenu::ProceedEventsMainMenu()
{
	if (mouseX >= buttonPanelX1 && mouseX <= buttonPanelX2 && mouseY >= buttonPanelY1 && mouseY <= buttonPanelY2)
	{
		for (int i = 1; i < 6; i++)
			HighlightButton(mainMenuButton[i]);
	}
	else
	{
		if (focusedButton != nullptr)
		{
			focusedButton->SetMouseOn(false);
			mouseOnButton = false;
			focusedButton = nullptr;
		}
	}
	if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
		return 0;
	if (focusedButton != nullptr && (mouseButtonPressedID == 1))
	{
		if (focusedButton->CompareLabel("Quit"))
			return 0;
		else
		{
			mouseButtonPressedID = 0;
			keyboardKeyPressedID = 0;

			if (focusedButton->CompareLabel("New Game"))
				return 1;
			else if (focusedButton->CompareLabel("Load Game"))
				return 2;
			else if (focusedButton->CompareLabel("Options"))
				return 3;
			else if (focusedButton->CompareLabel("Credits"))
				return 4;
		}
	}
	mouseButtonPressedID = 0;
	keyboardKeyPressedID = 0;
	return 5;
}

void MainMenu::HighlightButton(Button *testedButton)
{
	if (testedButton != nullptr)
	{
		if (testedButton->CompareCoords(mouseX, mouseY))
		{
			mouseOnButton = true;
			focusedButton = testedButton;
		}
		else
			testedButton->SetMouseOn(false);
	}
}

void MainMenu::CloseCharacterSelectionMenu(bool offset)
{
	if (warriorSelected == true)
	{
		warriorSelected = false;
		delete characterNameMenuButton;
		DeleteCharacterSelectionMenu(offset);
	}
	else
	{
		delete characterSelectionMenuButton[2];
		delete characterSelectionMenuButton[3];
	}
	if (focusedButton != nullptr)
	{
		focusedButton->SetMouseOn(false);
		mouseOnButton = false;
		focusedButton = nullptr;
	}

	NAME_EDIT = false;
	characterName = "Default";

	mouseButtonPressedID = 0;
	keyboardKeyPressedID = 0;
}

int MainMenu::ProceedEventsCharacterSelectionMenu(string outerCharacterName, bool *heroClass)
{
	if (focusedButton != nullptr)
	{
		if (!focusedButton->CompareCoords(mouseX, mouseY))
		{
			focusedButton->SetMouseOn(false);
			mouseOnButton = false;
			focusedButton = nullptr;
		}
	}
	else
	{
		mouseButtonPressedID = 0;
		//keyboardKeyPressedID = 0;
	}

	if ((mouseX >= 108 && mouseX <= 612 && mouseY >= 171 && mouseY <= 451))
	{		
		for (int i = 0; i < 4; i++)
			HighlightButton(characterSelectionMenuButton[i]);
		HighlightButton(characterNameMenuButton);
	}

	if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)	// natychmiastowe wyjscie do poprzedniego menu, 'sprzatanie' zmiennych przed powrotem
	{
		CloseCharacterSelectionMenu(!warriorSelected);
		return 1;
	}

	if (focusedButton != nullptr)
	{
		if (mouseButtonPressedID == 1)
		{
			mouseButtonPressedID = 0;
			keyboardKeyPressedID = 0;

			if (focusedButton->CompareLabel("Warrior"))	// zmiana widoku menu po kliknieciu na portret wojownika
			{
				if (warriorSelected == false)
				{
					warriorSelected = true;
					characterNameMenuButton = new Button(369, 211, 607, 241, true, true, characterName);
					characterSelectionMenuButton[0] = new Button(369, 416, 483, 446, true, false, "Return");
					characterSelectionMenuButton[1] = new Button(493, 416, 607, 446, true, false, "Confirm");
					delete characterSelectionMenuButton[3]; // usuniecie guzika z postacia czarodziejki
				}
				else
				{
					warriorSelected = false;
					delete characterNameMenuButton;
					delete characterSelectionMenuButton[0];
					delete characterSelectionMenuButton[1];
					characterSelectionMenuButton[3] = new Button(364, 171, 612, 451, false, false, "Wizard"); // przywrocenia guzika z postacia czarodziejki
				}
			}
			else if (focusedButton->CompareLabel(characterName))	// aktywacja lub deaktywacja pola do wpisywania nazwy postaci
			{
				NAME_EDIT = !NAME_EDIT;
				if (characterNameMenuButton->CompareLabel(""))	// jesli zostawimy puste pole podczas edycji, zostanie ono zmienione na domyslne
				{
					characterName = "Default";
					characterNameMenuButton->SetLabel(characterName);
				}
			}
			else if (focusedButton->CompareLabel("Confirm"))	// potwierdzenie wyboru i nazwy postaci - rozpoczecie gry
			{
				outerCharacterName = characterName;
				*heroClass = warriorSelected;
				CloseCharacterSelectionMenu(!warriorSelected);
				//LISTA WARUNKOW KTORA MUSI BYC SPELNIONA ABY ZACZAC GRE
				return 0;
			}
			else if (focusedButton->CompareLabel("Return"))	// powrot do glownego menu
			{
				CloseCharacterSelectionMenu(!warriorSelected);
				return 1;
			}
		}
	}

	if (NAME_EDIT == true)
	{
		if (characterNameMenuButton->CompareLabel("Default"))
		{
			characterName = "";
			characterNameMenuButton->SetLabel(characterName);
		}

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			try
			{
				if (keyboardKeyPressedID == ALLEGRO_KEY_BACKSPACE)
				{
					if (characterName.length() == 0)	// wyjatek gdy kasuje ostatni element!
						throw "Deleting from empty string";
					else
						characterName.pop_back();
				}
				else if (keyboardKeyPressedID == ALLEGRO_KEY_SPACE)
					characterName.push_back(' ');
				else if (keyboardKeyPressedID == ALLEGRO_KEY_ENTER)
				{
					if (characterName.length() == 0)	// wyjatek gdy zostawimy puste pole!
						throw "Character name cannot be empty!";
					else
						NAME_EDIT = false;
				}
				else if (keyboardKeyPressedID >= 1 && keyboardKeyPressedID <= 26)	// pomyslec nad obsluga malych liter
					if (characterName.length() < 16)
						characterName.push_back(keyboardKeyPressedID + 64);
			}
			catch (char*)	// obsluga wyjatku - ustawienie domyslnej nazwy postaci oraz wylaczenie edycji
			{
				characterName = "Default";
				NAME_EDIT = false;
			}
			characterNameMenuButton->SetLabel(characterName);
		}
	}


	return 5;
}

void MainMenu::LoadCharacterSelectionMenu()
{
	characterSelectionMenuButton[2] = new Button(108, 171, 356, 451, true, false, "Warrior");
	characterSelectionMenuButton[3] = new Button(364, 171, 612, 451, false, false, "Wizard");
}

void MainMenu::DeleteCharacterSelectionMenu(bool offset)	// metoda usuwa z pamieci guziki, zmienna offset informuje czy nalezy usuwac ostatni element tablicy czy zostal on juz usuniety
{
	for (int i = 0; i < 3 + offset; i++)
			delete characterSelectionMenuButton[i]; 
}

void MainMenu::DrawCharacterSelectionMenu()
{
	int index = 0;
	int mousex = 0, mousey = 0;
	int NAME_SET = 0;

	DrawMenu();
	// SUB-HEADER
	al_draw_filled_rounded_rectangle(108, 123, 612, 163, 8, 8, al_map_rgba(0, 0, 0, 125));
	al_draw_rounded_rectangle(108, 123, 612, 163, 8, 8, al_map_rgba(0, 0, 0, 150), 2);

	offSet = al_get_font_line_height(allegro_font->font20);
	al_draw_text(allegro_font->font20, allegro_font->WHITE, 355, ((163 + 123 - offSet) / 2), ALLEGRO_ALIGN_CENTRE, "Character Selection");

	// MID-FIELD-LEFT
	if (warriorSelected == false)
	{
		al_draw_bitmap(heroWarrior, 114, 179, 0);
		al_draw_filled_rounded_rectangle(108, 171, 356, 451, 8, 8, al_map_rgba(0, 0, 0, 150));
		al_draw_filled_rounded_rectangle(108, 171, 356, 451, 8, 8, al_map_rgba(0, 0, 0, 150));
		al_draw_rounded_rectangle(108, 171, 356, 451, 8, 8, al_map_rgba(0, 0, 0, 150), 2);
	}
	else
	{	
		al_draw_filled_rounded_rectangle(108, 171, 356, 451, 8, 8, al_map_rgba(0, 0, 0, 125));
		al_draw_bitmap(heroWarrior, 114, 179, 0);
		al_draw_rounded_rectangle(108, 171, 356, 451, 8, 8, al_map_rgba(0, 0, 0, 150), 2);
	}

	// MID-FIELD-RIGHT		
	if (warriorSelected == false)	// normalny widok
	{
		al_draw_bitmap(heroWizard, 370, 179, 0);
		al_draw_filled_rounded_rectangle(364, 171, 612, 451, 8, 8, al_map_rgba(0, 0, 0, 150));
		al_draw_rounded_rectangle(364, 171, 612, 451, 8, 8, al_map_rgba(0, 0, 0, 150), 2);
		al_draw_filled_rounded_rectangle(364, 171, 612, 451, 8, 8, al_map_rgba(0, 0, 0, 150));
		al_draw_text(allegro_font->font20, allegro_font->DARK_RED, (612 + 364) / 2, (451 + 171 - offSet) / 2, ALLEGRO_ALIGN_CENTRE, "NOT AVAILABLE");
	}
	else	// widok z okienkiem wpisywania nazwy postaci
	{
		al_draw_filled_rounded_rectangle(364, 171, 612, 451, 8, 8, al_map_rgba(0, 0, 0, 125));
		al_draw_rounded_rectangle(364, 171, 612, 451, 8, 8, al_map_rgba(0, 0, 0, 150), 2);

		offSet = al_get_font_line_height(allegro_font->font18);
		al_draw_text(allegro_font->font18, allegro_font->WHITE, 488, ((171 + 211 - offSet) / 2), ALLEGRO_ALIGN_CENTRE, "Type Character Name");

		characterNameMenuButton->DrawButton(allegro_font, offSet, al_map_rgba(0, 0, 0, 150), 8, 2);

		offSet = al_get_font_line_height(allegro_font->font12);
		if (NAME_EDIT == false)
			al_draw_text(allegro_font->font12, allegro_font->WHITE, 488, ((241 + 261 - offSet) / 2), ALLEGRO_ALIGN_CENTRE, "Edit mode: OFF");
		else
			al_draw_text(allegro_font->font12, allegro_font->WHITE, 488, ((241 + 261 - offSet) / 2), ALLEGRO_ALIGN_CENTRE, "Edit mode: ON");

		offSet = al_get_font_line_height(allegro_font->font18);
		characterSelectionMenuButton[0]->DrawButton(allegro_font, offSet, al_map_rgba(0, 0, 0, 125), 8, 1.5);
		characterSelectionMenuButton[1]->DrawButton(allegro_font, offSet, al_map_rgba(0, 0, 0, 125), 8, 1.5);			
	}
	al_draw_bitmap(cursor, mouseX, mouseY, 0);

	al_flip_display(); // wyœwietlenie aktualnego bufora na ekran
	al_clear_to_color(al_map_rgb(0, 0, 0)); // wyczyszczenie aktualnego bufora ekranu
}