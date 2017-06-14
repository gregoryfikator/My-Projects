#pragma once

#include <allegro5\allegro.h>

struct Resources
{
	//public:
		//ALLEGRO_BITMAP *background;
		//ALLEGRO_BITMAP *cursor;
		//ALLEGRO_BITMAP *heroWarrior;
		//ALLEGRO_BITMAP *heroWizard;

		//ALLEGRO_BITMAP *ui_eq;
		//ALLEGRO_BITMAP *ui_eq_list;
		//ALLEGRO_BITMAP *ui_eq_wear;
		//ALLEGRO_BITMAP *ui_quick;
		//ALLEGRO_BITMAP *ui_xp_bar;
		//ALLEGRO_BITMAP *ui_bin;

		//Resources()
		//{
	ALLEGRO_BITMAP *background = al_load_bitmap("data//textures//menu.png");
	ALLEGRO_BITMAP *cursor = al_load_bitmap("data//textures//cursor.png");
	ALLEGRO_BITMAP *heroWarrior = al_load_bitmap("data//textures//war.jpg");
	ALLEGRO_BITMAP *heroWizard = al_load_bitmap("data//textures//wiz.jpg");
	//}

	//bool LoadGameResources()
	//{
	ALLEGRO_BITMAP *ui_eq = al_load_bitmap("data//textures//ui_eq.png");
	ALLEGRO_BITMAP *ui_eq_list = al_load_bitmap("data//textures//ui_eq_list.png");
	ALLEGRO_BITMAP *ui_eq_wear = al_load_bitmap("data//textures//ui_eq_wear.png");
	ALLEGRO_BITMAP *ui_quick = al_load_bitmap("data//textures//ui_quick.png");
	ALLEGRO_BITMAP *ui_xp_bar = al_load_bitmap("data//textures//ui_xp_bar.png");
	ALLEGRO_BITMAP *ui_bin = al_load_bitmap("data//textures//ui_bin.png");

	ALLEGRO_SAMPLE_ID soundtrack1ID, soundtrack2ID;
	ALLEGRO_SAMPLE *soundtrack1 = al_load_sample("data//sounds//main00.ogg");
	ALLEGRO_SAMPLE *soundtrack2 = al_load_sample("data//sounds//main01.ogg");


	int	experienceThreshold[5] = { 100, 250, 500, 1000, 2000};


	//return true;
//}
	~Resources()
	{
		al_destroy_bitmap(ui_bin);
		al_destroy_bitmap(ui_xp_bar);
		al_destroy_bitmap(ui_quick);
		al_destroy_bitmap(ui_eq_wear);
		al_destroy_bitmap(ui_eq_list);
		al_destroy_bitmap(ui_eq);

		al_destroy_bitmap(heroWizard);
		al_destroy_bitmap(heroWarrior);
		al_destroy_bitmap(cursor);
		al_destroy_bitmap(background);

		al_destroy_sample(soundtrack1);
		al_destroy_sample(soundtrack2);
	}

};