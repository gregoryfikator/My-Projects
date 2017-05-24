#pragma once

#include "ALLEGRO_Init.h"
#include "ALLEGRO_Font.h"
#include "MainMenu.h"
#include "Hero.h"
#include "ManagerLocation.h"
#include "ManagerItem.h"
#include "ManagerSkill.h"


class GameLoop
{
	// resolution
	int			ScreenWidth;	//'X' dimension of game window
	int			ScreenHeight;	//'Y' dimension of game window

	// mouse coords
	int			MouseX;		//'X' coord of mouse pointer
	int			MouseY;		//'Y' coord of mouse pointer


	// pressed key id
	int			keyboardKeyPressedID;

	// flags
	bool		START_GAME;	//'true' = GameLoop running, 'false' = GameLoop breaking
	bool		LOAD_GAME;	//'true' = loading save, 'false' = starting new game
	bool		PLAY_GAME;	//'true' = game in progress, 'false' = starting new game
	bool		QUIT_GAME;	//'true' = quit game, 'false' = keep running
	
	/*
		SUKCESYWNIE ROZSZERZAC LISTE WSKAZNIKOW NA OBIEKTY WRAZ Z DODAWANIEM TYPOW
	*/

	ALLEGRO_BITMAP		*background;
	ALLEGRO_BITMAP		*cursor;
	ALLEGRO_BITMAP		*heroWarrior;
	ALLEGRO_BITMAP		*heroWizard;

	ALLEGRO_BITMAP		*ui_eq;
	ALLEGRO_BITMAP		*ui_eq_list;
	ALLEGRO_BITMAP		*ui_eq_wear;
	ALLEGRO_BITMAP		*ui_xp_bar;
	ALLEGRO_BITMAP		*ui_quick;
	ALLEGRO_BITMAP		*ui_bin;

	// pointers to objects
	ALLEGRO_Init		*allegro_init;
	ALLEGRO_Font		*allegro_font;
	ALLEGRO_DISPLAY		*window;
	ALLEGRO_TIMER		*timer;
	ALLEGRO_EVENT_QUEUE *event_queue;
	//Resources			*res;
	MainMenu			*mainmenu;

	string				outerCharacterName;
	bool				heroClass;
	enum Direction
	{
		NONE, KEY_W, KEY_A, KEY_S, KEY_D
	} direction;
	bool				keyState[4] = { false, false, false, false };

	bool				debugModeOn;
	bool				openEquipment;
	bool				openSkillTab;

	bool				redraw;
	int					STEP;

	Hero				*hero;
	ManagerLocation		*locationManager;
	ManagerItem			*itemManager;
	ManagerSkill		*skillManager;

public:
	GameLoop(int ScreenWidth_new, int ScreenHeight_new);
	//~GameLoop();

	// Methods

	void GameMenu();	// main menu of the game
	bool GamePlay();	// play the game
	bool InitResources();
	void HeroMovement();
	void DrawHud();
};