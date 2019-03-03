#include "init.h"
#include "game.h"
#include "snake.h"
#include "startmenu.h"
#include "plansza.h"

void startgame(int width, int height, int speed, bool *restart)
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
	*restart = false;
	int nwidth = width / SKOK, nheight = height / SKOK;

	ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0); //klatki na sekundê
	ALLEGRO_TIMER *timertimer = al_create_timer(1.0 / 1.0); //licznik czasu
	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue(); //kolejka eventow
	ALLEGRO_DISPLAY *disp = al_create_display(width, height);
	ALLEGRO_FONT *bigfont = al_load_font("fonts/Terminus.ttf", 60, 0);
	ALLEGRO_FONT *font = al_load_font("fonts/Terminus.ttf", 40, 0);
	ALLEGRO_FONT *smallfont = al_load_font("fonts/Terminus.ttf", 20, 0);
	ALLEGRO_BITMAP* shead = al_load_bitmap("images/shead.png");
	ALLEGRO_BITMAP* sbody = al_load_bitmap("images/sbody.png");
	ALLEGRO_BITMAP* sturn = al_load_bitmap("images/sturn.png");
	ALLEGRO_BITMAP* send = al_load_bitmap("images/send.png");
	ALLEGRO_BITMAP* mouse = al_load_bitmap("images/mouse.png");
	ALLEGRO_BITMAP* wall = al_load_bitmap("images/wall.jpg");
	ALLEGRO_BITMAP* holewall = al_load_bitmap("images/holewall.png");
	ALLEGRO_BITMAP* floor = al_load_bitmap("images/floor.png");
	ALLEGRO_BITMAP* blood = al_load_bitmap("images/blood.png");
	MUSTINITandREGISTER(timer, queue, disp, font, timertimer, shead, sbody, sturn, send, mouse, bigfont, smallfont, wall, holewall, floor, blood);

	bool done = false;
	bool redraw = true;
	ALLEGRO_EVENT event;

	bool gameover = false;
	bool wallcollision = false;
	int timeafterdeath = 0;
	int click2escapeAD = 45; //after death

	//szybkosc animacji 30=1s
	int speedS = speed; //ruch weza
	int speedA = 45; //pojawienie sie jablka

	int tab[200][200] = { 0 };
	initplansza(tab, width, height);

	// inicjacja wê¿a
	float x, y;
	int last = ALLEGRO_KEY_RIGHT;
	x = 120;
	y = 120;

	snake* waz = sinit(x, y, PRAWO, tab);

	srand(time(NULL) + getpid());
	float apple_x, apple_y;
	int nXmax = width / SKOK, nYmax = height / SKOK;
	int n_apple_x = 0, n_apple_y = 0;
	bool apple = false;
	int points = 0;

	al_start_timer(timer);
	al_start_timer(timertimer);
	while (1)
	{
		al_wait_for_event(queue, &event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:

			redraw = true;

			if (event.timer.count % speedS == 0 && !gameover)
			{
				if (checkapple(waz, last, tab))
				{
					points++;
					dodaj(waz, last, tab);
					apple = false;

					if (tab[n_apple_x][n_apple_y] == 2)
						tab[n_apple_x][n_apple_y] = 0;
				}
				else if (checkcollision(waz, last, tab))
				{
					gameover = true;
					przesun(waz, last, tab, width, &wallcollision);
					al_stop_timer(timertimer);
					timeafterdeath = al_get_timer_count(timer);
				}
				else
					przesun(waz, last, tab, width, &wallcollision);

			}

			if (event.timer.count % speedA == 0 && !apple && !gameover)
			{

				do {
					n_apple_x = losuj(1, nXmax - 2);
					n_apple_y = losuj(2, nYmax - 2);
				} while (tab[n_apple_x][n_apple_y] == 1);

				tab[n_apple_x][n_apple_y] = 2;
				apple_x = n_apple_x * 40;
				apple_y = n_apple_y * 40;

				apple = true;
			}

			break;

		case ALLEGRO_EVENT_KEY_DOWN:
			if (event.keyboard.keycode == ALLEGRO_KEY_UP && last != ALLEGRO_KEY_UP && waz->head->direction != DOL)
			{
				last = event.keyboard.keycode;
			}
			if (event.keyboard.keycode == ALLEGRO_KEY_DOWN && last != ALLEGRO_KEY_UP && waz->head->direction != GORA)
			{
				last = event.keyboard.keycode;
			}
			if (event.keyboard.keycode == ALLEGRO_KEY_LEFT && last != ALLEGRO_KEY_LEFT && waz->head->direction != PRAWO)
			{
				last = event.keyboard.keycode;
			}
			if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT && last != ALLEGRO_KEY_LEFT && waz->head->direction != LEWO)
			{
				last = event.keyboard.keycode;
			}

			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				done = true;

			if (gameover && event.keyboard.keycode == ALLEGRO_KEY_R)
			{
				done = true;
				*restart = true;
			}
			
			if (gameover && (al_get_timer_count(timer) - timeafterdeath > click2escapeAD))
				done = true;

			break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			done = true;
			break;
		}

		if (done)
			break;

		if (redraw && al_is_event_queue_empty(queue))
		{
			al_clear_to_color(al_map_rgb(0, 0, 0));

			for (int i = 1; i < nheight; i++) //malowanie podlogi
				for (int j = 0; j < nwidth; j++)
						al_draw_rotated_bitmap(floor, 0, 0, j*SKOK, i*SKOK, 0, 0);

			if (0) //wypisywanie podkladki w postaci tablicy dwuwymiarowej
				for (int i = 0; i < 20; i++)
					for (int j = 0; j < 20; j++)
						al_draw_textf(font, al_map_rgb(255, 255, 255), (float)i * 40, (float)j * 40, 0, "%d", tab[i][j]);

			
			for (int i = 0; i < nheight; i++) //malowanie scian
				for (int j = 0; j < nwidth; j++)
					if (tab[j][i] == SCIANA)
						al_draw_rotated_bitmap(wall, 0, 0, j*SKOK, i*SKOK, 0, 0);

			al_draw_textf(font, al_map_rgb(255, 255, 255), 100, 0, 0, "PUNKTY: %d", points);
			al_draw_textf(font, al_map_rgb(255, 255, 255), width - 280, 0, 0, "CZAS: %ld", al_get_timer_count(timertimer));

			snake_elem* elem_ptr = waz->last;
			bool first = true;
			while (elem_ptr != NULL)
			{
				float elem_x = elem_ptr->x;
				float elem_y = elem_ptr->y;
				int direction = elem_ptr->direction;
				int nastepny = elem_ptr->last;

				if (first) //ogon
				{
					if (nastepny == GORA)
						al_draw_rotated_bitmap(send, 0, 0, elem_x, elem_y, 0, 0);
					else if (nastepny == DOL)
						al_draw_rotated_bitmap(send, 0, 0, elem_x, elem_y, 0, ALLEGRO_FLIP_VERTICAL);
					else if (nastepny == PRAWO)
						al_draw_rotated_bitmap(send, 20, 20, elem_x + 20, elem_y + 20, ALLEGRO_PI / 2, 0);
					else // nastepny == LEWO
						al_draw_rotated_bitmap(send, 20, 20, elem_x + 20, elem_y + 20, ALLEGRO_PI / 2, ALLEGRO_FLIP_VERTICAL);

					first = false;
				}
				else if (elem_ptr->next == NULL) //glowa
				{
					if (direction == GORA)
						al_draw_rotated_bitmap(shead, 0, 0, elem_x, elem_y, 0, 0);
					else if (direction == DOL)
						al_draw_rotated_bitmap(shead, 0, 0, elem_x, elem_y, 0, ALLEGRO_FLIP_VERTICAL);
					else if (direction == PRAWO)
						al_draw_rotated_bitmap(shead, 20, 20, elem_x + 20, elem_y + 20, ALLEGRO_PI / 2, 0);
					else // direction == LEWO
						al_draw_rotated_bitmap(shead, 20, 20, elem_x + 20, elem_y + 20, ALLEGRO_PI / 2, ALLEGRO_FLIP_VERTICAL);
				}
				else //cialo
				{
					if (direction == GORA)
					{
						if (nastepny == GORA)
							al_draw_rotated_bitmap(sbody, 0, 0, elem_x, elem_y, 0, 0);
						else if (nastepny == PRAWO)
							al_draw_rotated_bitmap(sturn, 0, 0, elem_x, elem_y, 0, 0);
						else if (nastepny == LEWO)
							al_draw_rotated_bitmap(sturn, 0, 0, elem_x, elem_y, 0, ALLEGRO_FLIP_HORIZONTAL);

					}
					else if (direction == DOL)
					{
						if (nastepny == DOL)
							al_draw_rotated_bitmap(sbody, 0, 0, elem_x, elem_y, 0, ALLEGRO_FLIP_VERTICAL);
						else if (nastepny == PRAWO)
							al_draw_rotated_bitmap(sturn, 0, 0, elem_x, elem_y, 0, ALLEGRO_FLIP_VERTICAL);
						else if (nastepny == LEWO)
							al_draw_rotated_bitmap(sturn, 20, 20, elem_x + 20, elem_y + 20, ALLEGRO_PI / 2, ALLEGRO_FLIP_HORIZONTAL);

					}
					else if (direction == PRAWO)
					{
						if (nastepny == PRAWO)
							al_draw_rotated_bitmap(sbody, 20, 20, elem_x + 20, elem_y + 20, ALLEGRO_PI / 2, 0);
						else if (nastepny == GORA)
							al_draw_rotated_bitmap(sturn, 20, 20, elem_x + 20, elem_y + 20, ALLEGRO_PI / 2, ALLEGRO_FLIP_HORIZONTAL);
						else if (nastepny == DOL)
							al_draw_rotated_bitmap(sturn, 0, 0, elem_x, elem_y, 0, ALLEGRO_FLIP_HORIZONTAL);

					}
					else // direction == LEWO
					{
						if (nastepny == LEWO)
							al_draw_rotated_bitmap(sbody, 20, 20, elem_x + 20, elem_y + 20, ALLEGRO_PI / 2, ALLEGRO_FLIP_VERTICAL);
						else if (nastepny == GORA)
							al_draw_rotated_bitmap(sturn, 0, 0, elem_x, elem_y, 0, ALLEGRO_FLIP_VERTICAL);
						else if (nastepny == DOL)
							al_draw_rotated_bitmap(sturn, 0, 0, elem_x, elem_y, 0, 0);
					}

				}

				if (apple)
					al_draw_rotated_bitmap(mouse, 0, 0, apple_x, apple_y, 0, 0);

				elem_ptr = elem_ptr->next;
			}

			if (gameover)
			{

				int gr = 3; //grubosc ramki
				int ssz = 183, ksz = 185, swys = 80, kwys = 50;
				if (wallcollision)
					al_draw_rotated_bitmap(holewall, 0, 0, waz->head->x, waz->head->y, 0, 0);
				else
					al_draw_rotated_bitmap(blood, 0, 0, waz->head->x, waz->head->y, 0, 0);
				al_draw_filled_rectangle(width / 2 - ssz, height / 2 - swys, (width / 2) + ksz, (height / 2) + kwys, al_map_rgb(255, 255, 255));
				al_draw_filled_rectangle(width / 2 - ssz + gr, height / 2 - swys + gr, (width / 2) + ksz - gr, (height / 2) + kwys - gr, al_map_rgb(0, 0, 0));
				al_draw_textf(bigfont, al_map_rgb(255, 0, 0), width / 2 - 160, height / 2 - 60, 0, "KONIEC GRY!");
				
				if(al_get_timer_count(timer)-timeafterdeath > click2escapeAD)
					al_draw_textf(smallfont, al_map_rgb(255, 0, 0), width / 2 - 162, height / 2, 0, "Wcisnij dowolny klawisz, by wyjsc");
				else
					al_draw_textf(smallfont, al_map_rgb(255, 0, 0), width / 2 - 150, height / 2, 0, "Wcisnij \"R\" by zagrac ponownie");
			}


			al_flip_display();

			redraw = false;
		}

	}

	DESTROY(timer, queue, disp, font, timertimer, shead, sbody, sturn, send, mouse, bigfont, smallfont, wall, holewall, floor, blood);
}