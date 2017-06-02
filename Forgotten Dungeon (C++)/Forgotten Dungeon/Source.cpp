#define CRT_SECURE_NO_WARNINGS
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/keyboard.h>
#include <string>
#include "initAllegro.h"
#include "GameLoop.h"

using namespace std;

int main()
{
	GameLoop *gameLoop = new GameLoop(720, 480);
	gameLoop->GameMenu();
	
	delete gameLoop;
	
	return 0;
}

//int main(int argc, char **argv)
//{
//	if (!initAllegro())
//		;// obs³uga b³êdu inicjalizacji allegro (Wyrzucenie okna systemowego z bledem)
//		
//	//al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
//
//	ALLEGRO_DISPLAY *okno = al_create_display(1080, 720);
//	if (!okno)
//	{
//		al_show_native_message_box(okno, "FATAL ERROR", "COULDN'T CREATE DISPLAY", "There might be a problem with your graphic settings or graphic card.", "Close", ALLEGRO_MESSAGEBOX_ERROR);
//		return -1;
//	}
//
//	ALLEGRO_BITMAP *menu = al_load_bitmap("projekt//menu_0.png");
//	if (!menu)
//	{
//		al_show_native_message_box(okno, "FATAL ERROR", "COULDN'T LOAD BITMAP", "Bitmap 'projekt//menu_0.png' couldn't be loaded.                                  " "Out of memory or file is missing.", "Close", ALLEGRO_MESSAGEBOX_ERROR);
//		al_destroy_display(okno);
//		return -2;
//	}
//
//	ALLEGRO_BITMAP *buttons = al_load_bitmap("projekt//menu_buttons.png");
//	if (!buttons)
//	{
//		al_show_native_message_box(okno, "FATAL ERROR", "COULDN'T LOAD BITMAP", "Bitmap 'projekt//menu_buttons.png' couldn't be loaded.                        " "Out of memory or file is missing.", "Close", ALLEGRO_MESSAGEBOX_ERROR);
//		al_destroy_bitmap(menu);
//		al_destroy_display(okno);
//		return -2;
//	}
//
//	ALLEGRO_BITMAP *ch_menu = al_load_bitmap("projekt//ch_menu.png");
//	if (!ch_menu)
//	{
//		al_show_native_message_box(okno, "FATAL ERROR", "COULDN'T LOAD BITMAP", "Bitmap 'projekt//ch_menu.png' couldn't be loaded.                                 " "Out of memory or file is missing.", "Close", ALLEGRO_MESSAGEBOX_ERROR);
//		al_destroy_bitmap(buttons);
//		al_destroy_bitmap(menu);
//		al_destroy_display(okno);
//		return -2;
//	}
//
//	ALLEGRO_BITMAP *ch_buttons = al_load_bitmap("projekt//ch_menu_buttons.png");
//	if (!ch_buttons)
//	{
//		al_show_native_message_box(okno, "FATAL ERROR", "COULDN'T LOAD BITMAP", "Bitmap 'projekt//ch_menu_buttons.png' couldn't be loaded.                   " "Out of memory or file is missing.", "Close", ALLEGRO_MESSAGEBOX_ERROR);
//		al_destroy_bitmap(ch_menu);
//		al_destroy_bitmap(buttons);
//		al_destroy_bitmap(menu);
//		al_destroy_display(okno);
//		return -2;
//	}
//
//	ALLEGRO_BITMAP *cursor = al_load_bitmap("projekt//cursor.png");
//	if (!cursor)
//	{
//		al_show_native_message_box(okno, "FATAL ERROR", "COULDN'T LOAD BITMAP", "Bitmap 'projekt//cursor.png' couldn't be loaded.                                        " "Out of memory or file is missing.", "Close", ALLEGRO_MESSAGEBOX_ERROR);
//		al_destroy_bitmap(ch_buttons);
//		al_destroy_bitmap(ch_menu);
//		al_destroy_bitmap(buttons);
//		al_destroy_bitmap(menu);
//		al_destroy_display(okno);
//		return -2;
//	}
//
//	ALLEGRO_TIMER *timer = al_create_timer(1.0 / 120.0);
//	if (!timer)
//	{
//		al_show_native_message_box(okno, "FATAL ERROR", "UNKNOWN ERROR", "Couldn't initialize timer. Contact with support.", "Close", ALLEGRO_MESSAGEBOX_ERROR);
//		al_destroy_bitmap(cursor);
//		al_destroy_bitmap(ch_buttons);
//		al_destroy_bitmap(ch_menu);
//		al_destroy_bitmap(buttons);
//		al_destroy_bitmap(menu);
//		al_destroy_display(okno);
//		return -2;
//	}
//
//	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
//	if (!event_queue)
//	{
//		al_show_native_message_box(okno, "FATAL ERROR", "UNKNOWN ERROR", "Couldn't initialize event queue. Contact with support.", "Close", ALLEGRO_MESSAGEBOX_ERROR);
//		al_destroy_timer(timer);
//		al_destroy_bitmap(cursor);
//		al_destroy_bitmap(ch_buttons);
//		al_destroy_bitmap(ch_menu);
//		al_destroy_bitmap(buttons);
//		al_destroy_bitmap(menu);
//		al_destroy_display(okno);
//		return -2;
//	}
//	al_set_window_title(okno, "Forgotten Dungeon");
//	al_hide_mouse_cursor(okno);
//
//	al_draw_bitmap(menu, 0, 0, 0);
//	al_flip_display();
//
//	if (!timer)
//		return -1;
//
//	al_register_event_source(event_queue, al_get_keyboard_event_source());
//	al_register_event_source(event_queue, al_get_mouse_event_source());
//	al_register_event_source(event_queue, al_get_display_event_source(okno));
//	al_register_event_source(event_queue, al_get_timer_event_source(timer));
//
//	//string name = "";	//NAZWA POSTACI
//	//int count = 0;
//	//struct Saves save;
//	//strcpy(save.s1, name);
//	//strcpy(save.s2, name);
//	//strcpy(save.s3, name);
//	//strcpy(save.s4, name);
//	//strcpy(save.s5, name);
//
//	//// ZALADOWANIE Z PLIKU LISTY ZAPISANYCH POSTACI
//	//FILE *plik;
//	//plik = fopen("projekt//save//data", "rb");
//
//	//if (plik)
//	//{
//	//	fscanf(plik, "%s", save.s1);
//	//	fscanf(plik, "%s", save.s2);
//	//	fscanf(plik, "%s", save.s3);
//	//	fscanf(plik, "%s", save.s4);
//	//	fscanf(plik, "%s", save.s5);
//	//}
//	//fclose(plik);
//
//	int mousex = 0, mousey = 0;
//	Test *obiekt = new Test();
//	ALLEGRO_TRANSFORM trans;		// tego trzeba uzywac do zmiany rozdzielczosci zawartoœci bufora!!!
//	while (1)
//	{
//		ALLEGRO_EVENT ev;
//		al_wait_for_event(event_queue, &ev);
//
//		if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
//		{
//			mousex = ev.mouse.x;
//			mousey = ev.mouse.y;
//		}
//		obiekt->metoda();
//		//al_draw_bitmap(menu, 0, 0, 0);  // wyœwietlenie bitmapy "obrazek" na "Backbuffer" (bufor ekranu)
//		al_draw_bitmap(cursor, mousex, mousey, 0);
//		if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
//			break;
//
//		al_identity_transform(&trans);
//		al_scale_transform(&trans, 1.5, 1.5);	// wartosci beda zmiennymi ktore odpowiadaja za zmiane rozdzielczosci gry	0
//		al_use_transform(&trans);
//
//		//else if (mousex >= MENU_LX && mousex <= MENU_RX)
//		//{
//		//	if (mousey >= 100 && mousey <= 139) // x: 252-468 y: 100-139 (pozycja NEW GAME)
//		//	{
//		//		al_draw_bitmap(menu, 0, 0, 0);
//		//		al_draw_bitmap_region(buttons, 0, 0, BUTTON_X, BUTTON_Y, MENU_LX, 100, 0);
//		//		al_draw_bitmap(cursor, mousex, mousey, 0);
//		//		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1)
//		//			if (ch_select(okno, ch_menu, ch_buttons, cursor, event_queue, name) == 1)
//		//			{
//		//				game(okno, cursor, event_queue, timer, save, name, 0);
//		//			}
//		//	}
//		//	else if (mousey >= 148 && mousey <= 187) // x: 252-468 y: 148-187 (pozycja LOAD GAME)
//		//	{
//		//		al_draw_bitmap(menu, 0, 0, 0);
//		//		al_draw_bitmap_region(buttons, 0, 48, BUTTON_X, BUTTON_Y, MENU_LX, 148, 0);
//		//		al_draw_bitmap(cursor, mousex, mousey, 0);
//		//		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1)
//		//		{
//		//			// RYSOWANIE OKNA WYBORU ZAPISU DO WCZYTANIA
//		//			if (load_game(okno, cursor, event_queue, save, name) == 1)
//		//				game(okno, cursor, event_queue, timer, save, name, 1);
//		//		}
//		//	}
//		//	else if (mousey >= 244 && mousey <= 283) // x: 252-468 y: 244-283 (pozycja OPTIONS)
//		//	{
//		//		al_draw_bitmap(menu, 0, 0, 0);
//		//		al_draw_bitmap_region(buttons, 0, 144, BUTTON_X, BUTTON_Y, MENU_LX, 244, 0);
//		//		al_draw_bitmap(cursor, mousex, mousey, 0);
//		//	}
//		//	else if (mousey >= 292 && mousey <= 331) // x: 252-468 y: 292-331 (pozycja guzika CREDITS)
//		//	{
//		//		al_draw_bitmap(menu, 0, 0, 0);
//		//		al_draw_bitmap_region(buttons, 0, 192, BUTTON_X, BUTTON_Y, MENU_LX, 292, 0);
//		//		al_draw_bitmap(cursor, mousex, mousey, 0);
//		//	}
//		//	else if (mousey >= 340 && mousey <= 379) // x: 252-468 y: 340-379 (pozycja guzika QUIT)
//		//	{
//		//		al_draw_bitmap(menu, 0, 0, 0);
//		//		al_draw_bitmap_region(buttons, 0, 240, BUTTON_X, BUTTON_Y, MENU_LX, 340, 0);
//		//		al_draw_bitmap(cursor, mousex, mousey, 0);
//
//		//		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.mouse.button == 1)
//		//			break;
//		//	}
//		//}
//		al_flip_display(); // wyœwietlenie aktualnego bufora na ekran
//		al_clear_to_color(al_map_rgb(0, 0, 0)); // wyczyszczenie aktualnego bufora ekranu
//	}
//	al_rest(1);
//	al_destroy_event_queue(event_queue);
//	al_destroy_timer(timer);
//	al_destroy_bitmap(cursor);
//	al_destroy_bitmap(ch_buttons);
//	al_destroy_bitmap(ch_menu);
//	al_destroy_bitmap(buttons);
//	al_destroy_bitmap(menu);
//	al_destroy_display(okno);
//	return 0;
//}