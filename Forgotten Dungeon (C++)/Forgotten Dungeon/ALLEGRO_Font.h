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

public:
	ALLEGRO_Font();

	friend class MainMenu;
	friend class Button;
	friend class GameLoop;
	friend class ManagerItem;
	friend class ManagerSkill;
};