#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class Resources
{
public:
	Resources();
	~Resources();

	ALLEGRO_BITMAP *background;
	ALLEGRO_BITMAP *cursor;
	ALLEGRO_BITMAP *heroWarrior;
	ALLEGRO_BITMAP *heroWizard;

	ALLEGRO_BITMAP *ui_eq;
	ALLEGRO_BITMAP *ui_eq_list;
	ALLEGRO_BITMAP *ui_eq_wear;
	ALLEGRO_BITMAP *ui_quick;
	ALLEGRO_BITMAP *ui_xp_bar;
	ALLEGRO_BITMAP *ui_bin;

	ALLEGRO_SAMPLE_ID soundtrack1ID; 
	ALLEGRO_SAMPLE_ID soundtrack2ID;
	ALLEGRO_SAMPLE *soundtrack1;
	ALLEGRO_SAMPLE *soundtrack2;

	int	experienceThreshold[5];
};