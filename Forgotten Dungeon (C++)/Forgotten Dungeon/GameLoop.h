#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/keyboard.h>
#include <string>
#include "initAllegro.h"

#include "ALLEGRO_Init.h"
#include "ALLEGRO_Font.h"
#include "MainMenu.h"
#include "Resources.h"
#include "Hero.h"
#include "ManagerLocation.h"
#include "ManagerItem.h"
#include "ManagerSkill.h"
#include "ManagerFight.h"
#include <vld.h>


class GameLoop
{
	// resolution
	int			ScreenWidth;	//'X' dimension of game window
	int			ScreenHeight;	//'Y' dimension of game window

	// mouse coords
	int			MouseX;		//'X' coord of mouse pointer
	int			MouseY;		//'Y' coord of mouse pointer


	// pressed key id
	int			mouseButtonPressedID;
	bool		mouseLBPressed;
	int			keyboardKeyPressedID;

	// flags
	bool		START_GAME;	//'true' = GameLoop running, 'false' = GameLoop breaking
	bool		LOAD_GAME;	//'true' = loading save, 'false' = starting new game
	bool		PLAY_GAME;	//'true' = game in progress, 'false' = starting new game
	bool		QUIT_GAME;	//'true' = quit game, 'false' = keep running
	
	/*
		SUKCESYWNIE ROZSZERZAC LISTE WSKAZNIKOW NA OBIEKTY WRAZ Z DODAWANIEM TYPOW
	*/

	Resources			*resources;

	// pointers to objects
	ALLEGRO_Init		*allegro_init;
	ALLEGRO_Font		*allegro_font;
	ALLEGRO_DISPLAY		*window;
	ALLEGRO_TIMER		*timer;
	ALLEGRO_EVENT_QUEUE *event_queue;
	MainMenu			*mainmenu;

	string				outerCharacterName;
	bool				heroClass;
	enum Direction
	{
		NONE, KEY_W, KEY_A, KEY_S, KEY_D
	} direction, previousDirection;
	bool				keyState[4] = { false, false, false, false };

	bool				debugModeOn;
	bool				openEquipment;
	bool				openSkillTab;
	bool				fightInProgress;
	bool				pressedEscape;

	bool				redraw;
	int					STEP;
	int					heroAnimationCurrentFrame;
	int					heroAnimationDelay;
	int					heroAnimationFrameCount;

	Hero				*hero;
	ManagerLocation		*locationManager;
	ManagerItem			*itemManager;
	ManagerSkill		*skillManager;
	ManagerFight		*fightManager;
	// jak starczy czasu zamienic wszystkie na typ Manager, a w Managerze dodac metody virutalne przeladowywane w odpowiednich typach managerow
public:
	GameLoop(int ScreenWidth_new, int ScreenHeight_new);
	~GameLoop();


	// Methods

	void GameMenu();	// main menu of the game
	bool GamePlay();	// play the game
	bool InitResources();
	void GetAndProceedEvents();
	void HeroMovement();
	void HeroMovementAnimation();
	void DrawHud();
	void Escape();
};