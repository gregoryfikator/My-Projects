#include "ALLEGRO_Font.h"

ALLEGRO_Font::ALLEGRO_Font()
{
	al_init_font_addon();

	if (!al_init_ttf_addon())
		//fprintf(stderr, "failed to initialize allegro image addon!\n");
		delete this;

	font10 = al_load_ttf_font("projekt\\Vecna.otf", 10, 0);
	font12 = al_load_ttf_font("projekt\\Vecna.otf", 12, 0);
	font14 = al_load_ttf_font("projekt\\Vecna.otf", 14, 0);
	font18 = al_load_ttf_font("projekt\\Vecna.otf", 18, 0);
	font20 = al_load_ttf_font("projekt\\Vecna.otf", 20, 0);
	font40 = al_load_ttf_font("projekt\\Vecna.otf", 40, 0);

	DARK_RED = al_map_rgb(139, 0, 0);
	WHITE = al_map_rgb(255, 255, 255);
	LIGHT_GREEN = al_map_rgb(45, 210, 55);
	ORANGE = al_map_rgb(255, 142, 0);
	LIGHT_YELLOW = al_map_rgb(240, 230, 140);
	BLACK = al_map_rgb(0, 0, 0);
	TRANSPARENT_BLACK1 = al_map_rgba(0, 0, 0, 125);
	TRANSPARENT_BLACK2 = al_map_rgba(0, 0, 0, 150);
	TRANSPARENT_BLACK3 = al_map_rgba(0, 0, 0, 175);
	TRANSPARENT_BLACK4 = al_map_rgba(0, 0, 0, 200);
	TRANSPARENT_BLACK5 = al_map_rgba(0, 0, 0, 225);
	TRANSPARENT_BLACK6 = al_map_rgba(0, 0, 0, 250);
}

ALLEGRO_Font::~ALLEGRO_Font()
{
	al_destroy_font(font10);
	al_destroy_font(font12);
	al_destroy_font(font14);
	al_destroy_font(font18);
	al_destroy_font(font20);
	al_destroy_font(font40);
}