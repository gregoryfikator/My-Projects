#include "GameLoop.h"

GameLoop::GameLoop(int ScreenWidth_new, int ScreenHeight_new)
{
	START_GAME	= false;
	LOAD_GAME	= false;
	PLAY_GAME	= false;
	QUIT_GAME	= false;

	ScreenWidth		= ScreenWidth_new;
	ScreenHeight	= ScreenHeight_new;
	MouseX = ScreenWidth / 2;
	MouseY = ScreenHeight / 2;

	keyboardKeyPressedID = 0;

	allegro_init	= new ALLEGRO_Init();

	//al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	window = al_create_display(ScreenWidth, ScreenHeight);
	al_set_window_title(window, "Forgotten Dungeon");
	al_hide_mouse_cursor(window);

	allegro_font	= new ALLEGRO_Font();

	timer			= al_create_timer(1.0 / 60.0);
	event_queue		= al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(window));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	background = al_load_bitmap("data//textures//menu.png");
	cursor = al_load_bitmap("data//textures//cursor.png");
	heroWarrior = al_load_bitmap("data//textures//war.jpg");
	heroWizard = al_load_bitmap("data//textures//wiz.jpg");

	ui_eq = nullptr;
	ui_eq_list = nullptr;
	ui_eq_wear = nullptr;
	ui_xp_bar = nullptr;
	ui_quick = nullptr;
	ui_bin = nullptr;

	redraw = false;
	heroClass = true;
	direction = NONE;
	hero = nullptr;
	locationManager = nullptr;
	itemManager = nullptr;
	skillManager = nullptr;

	mainmenu		= new MainMenu(event_queue, allegro_font, background, cursor, heroWarrior, heroWizard);
	
	STEP			= 3;

	debugModeOn		= false;
	openEquipment	= false;
	openSkillTab	= false;
}

void GameLoop::GameMenu()
{
	do
	{
		mainmenu->DrawMainMenu();
		mainmenu->GetEvents();
		switch (mainmenu->ProceedEventsMainMenu())
		{
		case 0:
			QUIT_GAME = true;
			break;
		case 1:
			START_GAME = true;
			LOAD_GAME = false;
			// STARTING POINT OF NEW GAME
			break;
		case 2:
			START_GAME = true;
			LOAD_GAME = true;
			// LOADING GAME POINT
			break;
		case 3:
			// OPTIONS
			break;
		case 4:
			// CREDITS
			break;
		default:
			break;
		}

		if (START_GAME)
		{
			if (LOAD_GAME)
			{
				//okno wczytywania
			}
			else
			{
				mainmenu->LoadCharacterSelectionMenu();
				do
				{
					mainmenu->DrawCharacterSelectionMenu();
					mainmenu->GetEvents();
					switch (mainmenu->ProceedEventsCharacterSelectionMenu(outerCharacterName, &heroClass))
					{
					case 0:	// rozpoczecie nowej gry po wcisnieciu guzika Confirm
						PLAY_GAME = true;
						break;								
					case 1:	// powrot po wcisnieciu guzika Return lub klawisza ESC
						START_GAME = false;
						break;
					default:
						break;
					}
				} while (START_GAME && !PLAY_GAME);
				//okno tworzenia nowej postaci
				
			}
			if (START_GAME)
				GamePlay();

			START_GAME = false;
			LOAD_GAME = false;
			PLAY_GAME = false;
		}
	} while (!QUIT_GAME);

	//delete this;
}

bool GameLoop::InitResources()
{
	srand(time(NULL));
	// TUTAJ BEDA WYKORZYSTYWANE WATKI
	locationManager = new ManagerLocation();
	locationManager->Init("data//location//village001.jpg", "data//location//village001");

	itemManager = new ManagerItem();
	itemManager->Init();

	skillManager = new ManagerSkill();
	skillManager->Init();

	hero = new Hero(outerCharacterName, heroClass, "projekt//characters//sprite//test.png", ScreenWidth / 2, ScreenHeight / 2);
	
	
	for (int i = 0; i < 20; i++)
		hero->AssignNewItem(new Item(itemManager->DropItem()));

	this->ui_eq = al_load_bitmap("data//textures//ui_eq.png");
	this->ui_eq_list = al_load_bitmap("data//textures//ui_eq_list.png");
	this->ui_eq_wear = al_load_bitmap("data//textures//ui_eq_wear.png");
	this->ui_quick = al_load_bitmap("data//textures//ui_quick.png");
	this->ui_xp_bar = al_load_bitmap("data//textures//ui_xp_bar.png");
	this->ui_bin = al_load_bitmap("data//textures//ui_bin.png");

	/*
	TO DO:
	- widok ekwipunku bohatera z oskryptowaniem
	- umiejêtnoœci, widok okna umiejêtnoœci
	- HUD: panele z guzikami (do w³¹czania ekwipunku, okna statystyk, okna menu), panel podgl¹du postaci, panel podgl¹du przeciwnika/NPC po najechaniu kursorem
	*/


	//koordynaty bohatera po smierci -> (861, 168)
	direction = NONE;
	redraw = true;

	return true;
}

bool GameLoop::GamePlay()
{
	ALLEGRO_EVENT_QUEUE *event_queue2 = al_create_event_queue();
	al_register_event_source(event_queue2, al_get_mouse_event_source());
	if (InitResources())
	{
		al_start_timer(timer);
		do
		{
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);
			if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
			{
				MouseX = ev.mouse.x;
				MouseY = ev.mouse.y;
			}
			if (ev.type == ALLEGRO_EVENT_TIMER)
			{
				if (openEquipment == false && openSkillTab == false)
					HeroMovement();
				redraw = true;
			}
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				keyboardKeyPressedID = ev.keyboard.keycode;

				if (keyboardKeyPressedID == ALLEGRO_KEY_I)
				{
					openSkillTab = false;
					openEquipment = !openEquipment;
				}
				if (keyboardKeyPressedID == ALLEGRO_KEY_T)
				{
					openEquipment = false;
					openSkillTab = !openSkillTab;
				}
				if (keyboardKeyPressedID == ALLEGRO_KEY_P)
				{
					debugModeOn = !debugModeOn;
				}

				keyboardKeyPressedID = 0;
			}

			if (redraw)// && al_is_event_queue_empty(event_queue))
			{
				redraw = false;
				locationManager->DrawCurrentLocation();
				hero->DrawCharacter();
				this->DrawHud();

				if (openEquipment == true)
				{
					// rysowanie ekwipunku
					al_draw_filled_rectangle(0, 0, 720, 480, al_map_rgba(0, 0, 0, 175));
					al_draw_bitmap(ui_eq, 30, 43, 0);
					al_draw_filled_rounded_rectangle(282, 341, 282 + 20, 362, 2, 2, al_map_rgb(45, 210, 55)); //al_draw_filled_rounded_rectangle(282, 341, 282 + x_percent_part, 362, 2, 2, al_map_rgb(45, 210, 55));
					al_draw_bitmap(ui_xp_bar, 259, 305, 0);

					// tutaj powinny byc rysowane efekty jak podswietlenie czy przyciemnienie przedmiotow w ekwipunku

					hero->DrawItemsFromBackpack();

					al_draw_bitmap(ui_eq_list, 64, 107, 0);
					al_draw_bitmap(ui_eq_wear, 258, 107, 0);

					if (debugModeOn) // docelowo kosz staje sie aktywny i mozna usunac przedmiot gdy zostanie zaznaczony
						al_draw_bitmap(ui_bin, 53, 379, 0);

				}
				else if (openSkillTab == true)
				{
					// rysowanie okna umiejêtnoœci
				}

				if (debugModeOn == true)	// wlaczenie trybu debugowania wyswietla wspolrzedne postaci oraz kursora
				{
					al_draw_textf(allegro_font->font20, al_map_rgb(139, 0, 0), 635, 2, 0, "Hx1 = %3d", locationManager->GetXPos() + hero->GetX1Pos());
					al_draw_textf(allegro_font->font20, al_map_rgb(139, 0, 0), 635, 22, 0, "Hy1 = %3d", locationManager->GetYPos() + hero->GetY1Pos());
					al_draw_textf(allegro_font->font20, al_map_rgb(139, 0, 0), 630, 45, 0, "Hx2 = %3d", locationManager->GetXPos() + hero->GetX2Pos());
					al_draw_textf(allegro_font->font20, al_map_rgb(139, 0, 0), 630, 65, 0, "Hy2 = %3d", locationManager->GetYPos() + hero->GetY2Pos());
					al_draw_textf(allegro_font->font20, al_map_rgb(139, 0, 0), 630, 85, 0, "Mx1 = %3d", MouseX);
					al_draw_textf(allegro_font->font20, al_map_rgb(139, 0, 0), 630, 105, 0, "My1 = %3d", MouseY);
				}

				al_draw_bitmap(cursor, MouseX, MouseY, 0);

				al_flip_display(); // wyœwietlenie aktualnego bufora na ekran
				al_clear_to_color(al_map_rgb(0, 0, 0)); // wyczyszczenie aktualnego bufora ekranu
			}
			
		} while (true);

	}
	return false;
}

void GameLoop::HeroMovement()
{
	int mapX = locationManager->GetCurrentLocation()->GetXPos();
	int mapY = locationManager->GetCurrentLocation()->GetYPos();
	int heroX = hero->GetX1Pos();
	int heroY = hero->GetY1Pos();

	ALLEGRO_KEYBOARD_STATE keyboard;
	al_get_keyboard_state(&keyboard);

	if (al_key_down(&keyboard, ALLEGRO_KEY_W))
	{
		direction = KEY_W;
		if (!locationManager->ColisionTest(heroX, heroY, hero->GetX2Pos(), hero->GetY2Pos(), direction))
		{
			if (mapY > 0 && heroY == 240)
				locationManager->GetCurrentLocation()->SetYPos(-STEP);
			else if (mapY == 0 && heroY >= 3 || mapY == 1020 && (heroY > 240 || heroY == 448))
				hero->SetYPos(-STEP);
		}	
	}
	if (al_key_down(&keyboard, ALLEGRO_KEY_A))
	{
		direction = KEY_A;
		if (!locationManager->ColisionTest(heroX, heroY, hero->GetX2Pos(), hero->GetY2Pos(), direction))
		{
			if (mapX > 0 && heroX == 360)
				locationManager->GetCurrentLocation()->SetXPos(-STEP);
			else if (mapX == 0 && heroX >= 3 || mapX == 780 && (heroX > 360 || heroX == 688))
				hero->SetXPos(-STEP);
		}
	}
	if (al_key_down(&keyboard, ALLEGRO_KEY_S))
	{
		direction = KEY_S;
		if (!locationManager->ColisionTest(heroX, heroY, hero->GetX2Pos(), hero->GetY2Pos(), direction))
		{
			if (mapY < 1020 && heroY == 240)
				locationManager->GetCurrentLocation()->SetYPos(STEP);
			else if (mapY == 1020 && heroY <= 445 || mapY == 0 && (heroY < 240 || heroY == 0))
				hero->SetYPos(STEP);
		}
	}
	if (al_key_down(&keyboard, ALLEGRO_KEY_D))
	{
		direction = KEY_D;
		if (!locationManager->ColisionTest(heroX, heroY, hero->GetX2Pos(), hero->GetY2Pos(), direction))
		{
			if (mapX < 780 && heroX == 360)
				locationManager->GetCurrentLocation()->SetXPos(STEP);
			else if (mapX == 780 && heroX <= 685 || mapX == 0 && (heroX < 360 || heroX == 0))
				hero->SetXPos(STEP);
		}
	}
	direction = NONE;
}

void GameLoop::DrawHud()
{
	al_draw_filled_rounded_rectangle(5, 420, 60, 475, 8, 8, al_map_rgba(0, 0, 0, 75));
	al_draw_rounded_rectangle(5, 420, 60, 475, 8, 8, al_map_rgba(0, 0, 0, 175), 2.5);
	al_draw_bitmap(ui_quick, 167, 422, 0);
}