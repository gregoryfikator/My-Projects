#include "GameLoop.h"

GameLoop::GameLoop(int ScreenWidth_new, int ScreenHeight_new)
{
	START_GAME	= false;
	LOAD_GAME	= false;
	PLAY_GAME	= false;
	QUIT_GAME	= false;

	ScreenWidth				= ScreenWidth_new;
	ScreenHeight			= ScreenHeight_new;
	MouseX					= ScreenWidth / 2;
	MouseY					= ScreenHeight / 2;

	mouseButtonPressedID	= 0;
	mouseLBPressed			= false;
	keyboardKeyPressedID	= 0;

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

	resources = new Resources();

	direction			= NONE;
	previousDirection	= NONE;

	redraw				= true;
	heroClass			= true;
	
	hero				= nullptr;
	locationManager		= nullptr;
	itemManager			= nullptr;
	skillManager		= nullptr;
	fightManager		= nullptr;

	mainmenu			= new MainMenu(event_queue, allegro_font, resources->background, resources->cursor, resources->heroWarrior, resources->heroWizard, resources->soundtrack1, &resources->soundtrack1ID);
	
	STEP		= 3;

	heroAnimationCurrentFrame	= 1;
	heroAnimationDelay			= 7;
	heroAnimationFrameCount		= 0;

	debugModeOn		= false;
	openEquipment	= false;
	openSkillTab	= false;
	fightInProgress = false;
	pressedEscape	= false;
}

GameLoop::~GameLoop()
{
	delete mainmenu;
	delete resources;
	delete allegro_font;
	delete allegro_init;

	delete hero;
	delete itemManager;
	delete skillManager;
	delete locationManager;
	delete fightManager;
	
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(window);
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
					switch (mainmenu->ProceedEventsCharacterSelectionMenu(&outerCharacterName, &heroClass))
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
}

bool GameLoop::InitResources()
{
	srand(time(nullptr));
	// TUTAJ BEDA WYKORZYSTYWANE WATKI
	locationManager = new ManagerLocation();
	locationManager->Init("data//location//village001.jpg", "data//location//village001", "data//character//characterlist.txt");

	itemManager = new ManagerItem();
	itemManager->Init();

	skillManager = new ManagerSkill();
	skillManager->Init();

	fightManager = new ManagerFight();

	if (heroClass)
		hero = new Hero(outerCharacterName, heroClass, "data//character//bmp//heroSprite.png", ScreenWidth / 2, ScreenHeight / 2, resources->heroWarrior, LOAD_GAME);
	else
		hero = new Hero(outerCharacterName, heroClass, "data//character//bmp//heroSprite.png", ScreenWidth / 2, ScreenHeight / 2, resources->heroWizard, LOAD_GAME);

	hero->AssignNewItem(new Item(itemManager->DropItem(true)));		

	skillManager->AquireSkill(hero);

	al_stop_sample(&resources->soundtrack1ID);
	al_play_sample(resources->soundtrack2, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &resources->soundtrack2ID);
	//koordynaty bohatera po smierci -> (861, 168) // w przyszlosci npc umozliwiajacy wskrzeszanie
	return true;
}

bool GameLoop::GamePlay()
{
	if (InitResources())
	{
		al_start_timer(timer);
		do
		{
			GetAndProceedEvents();

			if (redraw)
			{
				redraw = false;
				locationManager->DrawCurrentLocation();
				locationManager->DrawSpawnedEnemies();

				al_draw_bitmap(hero->getHeroAnimationFrame(heroAnimationCurrentFrame), hero->GetX1Pos(), hero->GetY1Pos(), 0);

				if (locationManager->GetFightStatus())	// true -> walka
				{
					al_draw_filled_rectangle(0, 0, 150, 150, allegro_font->DARK_RED);
					if (fightInProgress == false)
					{
						fightManager->Init(hero, static_cast<Enemy *>(locationManager->GetEnemy()));
						fightInProgress = true;
					}
					fightManager->Draw(resources, allegro_font);
					if (fightManager->Fight() == true)	// wygrana walka
					{
						
						if (fightManager->GetFightStatus() == true)
						{
							if (fightManager->CheckIfHeroEscaped() == false)
							{
								// drop itemow, ++exp
								hero->heroStats->exp += 10 * locationManager->GetEnemy()->GetLevel();
								itemManager->ChangeXPBarLength(hero->heroStats->exp, resources->experienceThreshold[hero->GetLevel() - 1]);
								fightManager->EndFight();
								if (rand() % 100 % 2 == 0)
									hero->AssignNewItem(new Item(itemManager->DropItem()));

								skillManager->DropPotions();
								locationManager->KillEnemy();
								locationManager->RespawnEnemy();
							}
							else
							{
								this->Escape();
								fightManager->ResetHeroEscaped();
							}

							locationManager->SetFightStatus(false);
							fightInProgress = false;
						}
					}
					else 
					{
						if (fightManager->GetFightStatus() == true)
						{
							pressedEscape = true;// koniec gry
							QUIT_GAME = true;

							fightManager->EndFight();
							locationManager->SetFightStatus(false);
							fightInProgress = false;
						}
					}
					
				}

				this->DrawHud();
				if (openEquipment == true)
				{			
					if (itemManager->CheckButtons(MouseX, MouseY, hero, mouseLBPressed))
					{
						itemManager->CheckCursorOverlayBackpackAndClick(MouseX, MouseY, hero, mouseLBPressed);
						itemManager->CheckCursorOverlayWearingAndClick(MouseX, MouseY, hero, mouseLBPressed);
						if (itemManager->CheckRecalculation() == true)
							itemManager->RecalculateStats(hero);

						itemManager->Draw(hero, resources, allegro_font);

						//wyswietlanie opisu przedmiotu po najechaniu kursorem
						if (itemManager->GetOverlayBackpack())
							itemManager->DrawDescription(MouseX, MouseY, hero->GetItemFromBackpack(itemManager->GetOverlayedItemIndex()), allegro_font);
						else
							itemManager->DrawDescription(MouseX, MouseY, hero->GetItemFromEquipment(itemManager->GetOverlayedItemIndex()), allegro_font);
					}
					else
						openEquipment = false;

					if (hero->heroStats->exp >= resources->experienceThreshold[hero->GetLevel() - 1])
					{
						hero->heroStats->exp = hero->heroStats->exp - resources->experienceThreshold[hero->GetLevel() - 1];
						hero->IncreaseLevel();
					}
				}
				else if (openSkillTab == true)
				{
					if (skillManager->CheckButtons(MouseX, MouseY, hero, mouseLBPressed))
					{
						skillManager->CheckCursorOverlayTabAndClick(MouseX, MouseY, hero, mouseLBPressed);
						skillManager->CheckCursorOverlayDockAndClick(MouseX, MouseY, hero, mouseLBPressed, openSkillTab);

						skillManager->Draw(resources, allegro_font);

						skillManager->DrawDockedSkills(MouseX, MouseY, hero, allegro_font, openEquipment, openSkillTab);
						al_draw_bitmap(resources->ui_quick, 167, 421, 0);
						skillManager->DrawSelectedSkill(MouseX, MouseY, hero);
						//wyswietlanie opisu umiejetnosci po najechaniu kursorem
						skillManager->DrawDescription(MouseX, MouseY, hero, skillManager->GetSkill(), allegro_font);
					}
					else
						openSkillTab = false;
				}

				if (openSkillTab == false)
				{
					skillManager->CheckCursorOverlayDockAndClick(MouseX, MouseY, hero, mouseLBPressed, openSkillTab);
					skillManager->DrawDescription(MouseX, MouseY, hero, skillManager->GetSkill(), allegro_font);
				}

				if (debugModeOn == true)	// wlaczenie trybu debugowania wyswietla wspolrzedne postaci oraz kursora
				{
					al_draw_textf(allegro_font->font20, allegro_font->DARK_RED, 635, 2, 0, "Hx1 = %3d", locationManager->GetXPos() + hero->GetX1Pos());
					al_draw_textf(allegro_font->font20, allegro_font->DARK_RED, 635, 22, 0, "Hy1 = %3d", locationManager->GetYPos() + hero->GetY1Pos());
					al_draw_textf(allegro_font->font20, allegro_font->DARK_RED, 630, 45, 0, "Hx2 = %3d", locationManager->GetXPos() + hero->GetX2Pos());
					al_draw_textf(allegro_font->font20, allegro_font->DARK_RED, 630, 65, 0, "Hy2 = %3d", locationManager->GetYPos() + hero->GetY2Pos());
					al_draw_textf(allegro_font->font20, allegro_font->DARK_RED, 630, 85, 0, "Mx1 = %3d", MouseX);
					al_draw_textf(allegro_font->font20, allegro_font->DARK_RED, 630, 105, 0, "My1 = %3d", MouseY);
				}

				mouseLBPressed = false;

				al_draw_bitmap(resources->cursor, MouseX, MouseY, 0);

				al_flip_display(); // wyœwietlenie aktualnego bufora na ekran
				al_clear_to_color(al_map_rgb(0, 0, 0)); // wyczyszczenie aktualnego bufora ekranu			
			}		

			if (pressedEscape == true)
			{
				pressedEscape = false;
				break;
			}
		} while (true);
	}
	return false;
}

void GameLoop::GetAndProceedEvents()
{
	ALLEGRO_EVENT ev;
	al_wait_for_event(event_queue, &ev);
	if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		MouseX = ev.mouse.x;
		MouseY = ev.mouse.y;
	}
	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		mouseButtonPressedID = ev.mouse.button;

		if (mouseButtonPressedID == 1)
		{
			mouseLBPressed = true;
		}

		mouseButtonPressedID = 0;
	}
	if (ev.type == ALLEGRO_EVENT_TIMER)
	{
		if (openEquipment == false && openSkillTab == false && locationManager->GetFightStatus() == false)
		{
			HeroMovement();
			HeroMovementAnimation();
		}
		redraw = true;
	}
	if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		keyboardKeyPressedID = ev.keyboard.keycode;

		if (locationManager->GetFightStatus() == false)
		{
			if (keyboardKeyPressedID == ALLEGRO_KEY_I)
			{
				openSkillTab = false;
				openEquipment = !openEquipment;
			}
			if (keyboardKeyPressedID == ALLEGRO_KEY_T)
			{
				openEquipment = false;
				openSkillTab = !openSkillTab;
				if (openSkillTab == false)
					skillManager->ResetSkillTab();
			}
			if (keyboardKeyPressedID == ALLEGRO_KEY_P)
			{
				debugModeOn = !debugModeOn;
			}
			if (keyboardKeyPressedID == ALLEGRO_KEY_ESCAPE)
			{
				pressedEscape = true;
			}
		}
		else if (keyboardKeyPressedID == ALLEGRO_KEY_1 || keyboardKeyPressedID == ALLEGRO_KEY_2 || keyboardKeyPressedID == ALLEGRO_KEY_3 || keyboardKeyPressedID == ALLEGRO_KEY_4 || keyboardKeyPressedID == ALLEGRO_KEY_5 || keyboardKeyPressedID == ALLEGRO_KEY_6)
			fightManager->SetUsedSkill(keyboardKeyPressedID - ALLEGRO_KEY_1);
		keyboardKeyPressedID = 0;
	}
}

void GameLoop::HeroMovement()
{
	int mapX = locationManager->GetCurrentLocation()->GetXPos();
	int mapY = locationManager->GetCurrentLocation()->GetYPos();
	int heroX = hero->GetX1Pos();
	int heroY = hero->GetY1Pos();

	ALLEGRO_KEYBOARD_STATE keyboard;
	al_get_keyboard_state(&keyboard);

	previousDirection = direction;
	direction = NONE;

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
}

void GameLoop::HeroMovementAnimation()
{
	if (direction == NONE)
	{
		heroAnimationCurrentFrame = 1;
		heroAnimationFrameCount = 0;
	}
	else if (direction == KEY_S)
	{
		if (previousDirection != direction)
		{
			heroAnimationFrameCount = 0;
			heroAnimationCurrentFrame = 1;
		}

		if (++heroAnimationFrameCount >= heroAnimationDelay)
		{
			if (++heroAnimationCurrentFrame >= 3)
				heroAnimationCurrentFrame = 0;

			heroAnimationFrameCount = 0;
		}
	}
	else if (direction == KEY_A)
	{
		if (previousDirection != direction)
		{
			heroAnimationFrameCount = 0;
			heroAnimationCurrentFrame = 4;
		}

		if (++heroAnimationFrameCount >= heroAnimationDelay)
		{
			if (++heroAnimationCurrentFrame >= 6)
				heroAnimationCurrentFrame = 3;

			heroAnimationFrameCount = 0;
		}
	}
	else if (direction == KEY_D)
	{
		if (previousDirection != direction)
		{
			heroAnimationFrameCount = 0;
			heroAnimationCurrentFrame = 7;
		}

		if (++heroAnimationFrameCount >= heroAnimationDelay)
		{
			if (++heroAnimationCurrentFrame >= 9)
				heroAnimationCurrentFrame = 6;

			heroAnimationFrameCount = 0;
		}
	}
	else if (direction == KEY_W)
	{
		if (previousDirection != direction)
		{
			heroAnimationFrameCount = 0;
			heroAnimationCurrentFrame = 10;
		}

		if (++heroAnimationFrameCount >= heroAnimationDelay)
		{
			if (++heroAnimationCurrentFrame >= 12)
				heroAnimationCurrentFrame = 9;

			heroAnimationFrameCount = 0;
		}
	}
}

void GameLoop::DrawHud()
{
	if (openSkillTab == false)
	{
		skillManager->DrawDockedSkills(MouseX, MouseY, hero, allegro_font, openEquipment, openSkillTab);
		al_draw_bitmap(resources->ui_quick, 167, 421, 0);
	}
}

void GameLoop::Escape()
{
	hero->SetCharacterStartPoint(360, 240);
	locationManager->GetCurrentLocation()->EscapeToStartPoint();
}