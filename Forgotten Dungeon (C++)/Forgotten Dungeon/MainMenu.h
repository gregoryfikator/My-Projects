#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "ALLEGRO_Font.h"
#include "Button.h"
#include "Resources.h"

using namespace std;

class MainMenu
{
	ALLEGRO_BITMAP		*background;
	ALLEGRO_BITMAP		*cursor;
	ALLEGRO_BITMAP		*heroWarrior;
	ALLEGRO_BITMAP		*heroWizard;

	ALLEGRO_SAMPLE		*soundtrack[2];


	string				characterName;

	ALLEGRO_EVENT		ev;
	ALLEGRO_EVENT_QUEUE *event_queue;
	
	ALLEGRO_Font		*allegro_font;
	Button				*mainMenuButton[6];
	Button				*characterSelectionMenuButton[4];
	Button				*characterNameMenuButton;
	Button				*focusedButton;

	int			mouseX;
	int			mouseY;
	int			mouseButtonPressedID;
	bool		mouseOnButton;

	bool		warriorSelected;
	bool		popupMenu;

	bool		NAME_EDIT;

	int			keyboardKeyPressedID;

	int			buttonPanelX1;
	int			buttonPanelY1;
	int			buttonPanelX2;
	int			buttonPanelY2;

	int			offSet;		// used for holding calculated shift of vertical text position (based on font height)

public:
	MainMenu(ALLEGRO_EVENT_QUEUE *event_queue_new, ALLEGRO_Font *allegro_font_new, ALLEGRO_BITMAP *background_, ALLEGRO_BITMAP *cursor_, ALLEGRO_BITMAP *heroWarrior_, ALLEGRO_BITMAP *heroWizzard_, ALLEGRO_SAMPLE *soundtrack, ALLEGRO_SAMPLE_ID *soundtrackID);
	~MainMenu();

	void	DrawMenu();
	void	DrawMainMenu();
	void	HighlightButton(Button *testedButton);

	void	GetEvents();
	int		ProceedEventsMainMenu(bool *START_GAME);
	int		ProceedEventsCharacterSelectionMenu(string *outerCharacterName, bool *heroClass);

	void	LoadCharacterSelectionMenu();
	void	DrawCharacterSelectionMenu();
	void    CloseCharacterSelectionMenu(bool offset);
	void	DeleteCharacterSelectionMenu(bool offset);
};