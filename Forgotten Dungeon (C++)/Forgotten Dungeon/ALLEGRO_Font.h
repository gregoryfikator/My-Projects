#pragma once

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class ALLEGRO_Font
{
	ALLEGRO_FONT *font12;
	ALLEGRO_FONT *font18;
	ALLEGRO_FONT *font20;
	ALLEGRO_FONT *font40;

	ALLEGRO_COLOR DARK_RED;
	ALLEGRO_COLOR WHITE;
	ALLEGRO_COLOR LIGHT_GREEN;
	ALLEGRO_COLOR ORANGE;
	ALLEGRO_COLOR LIGHT_YELLOW;
	ALLEGRO_COLOR BLACK;
	ALLEGRO_COLOR TRANSPARENT_BLACK1;	// alpha: 125
	ALLEGRO_COLOR TRANSPARENT_BLACK2;	// alpha: 150
	ALLEGRO_COLOR TRANSPARENT_BLACK3;	// alpha: 175
	ALLEGRO_COLOR TRANSPARENT_BLACK4;	// alpha: 200
	ALLEGRO_COLOR TRANSPARENT_BLACK5;	// alpha: 225
	ALLEGRO_COLOR TRANSPARENT_BLACK6;	// alpha: 250
public:
	ALLEGRO_Font();

	friend class MainMenu;
	friend class Button;
	friend class GameLoop;
	friend class ManagerItem;
	friend class ManagerSkill;
};