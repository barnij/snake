#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h> 
#ifdef _WIN32
#include <windows.h> 
#endif
#ifdef __unix__
#include <unistd.h>
#endif
#define SKOK 40

void must_init(bool test, const char *description);

void INIT();

void SETDISPLAY();

void MUSTINITandREGISTER(ALLEGRO_TIMER *timer, ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_DISPLAY *disp, ALLEGRO_FONT *font, ALLEGRO_TIMER *timertimer, ALLEGRO_BITMAP* shead, ALLEGRO_BITMAP* sbody, ALLEGRO_BITMAP* sturn, ALLEGRO_BITMAP* send, ALLEGRO_BITMAP* mouse, ALLEGRO_FONT *bigfont, ALLEGRO_FONT *smallfont, ALLEGRO_BITMAP* wall, ALLEGRO_BITMAP* holewall, ALLEGRO_BITMAP* floor, ALLEGRO_BITMAP* blood);

void DESTROY(ALLEGRO_TIMER *timer, ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_DISPLAY *disp, ALLEGRO_FONT *font, ALLEGRO_TIMER *timertimer, ALLEGRO_BITMAP* shead, ALLEGRO_BITMAP* sbody, ALLEGRO_BITMAP* sturn, ALLEGRO_BITMAP* send, ALLEGRO_BITMAP* mouse, ALLEGRO_FONT *bigfont, ALLEGRO_FONT *smallfont, ALLEGRO_BITMAP* wall, ALLEGRO_BITMAP* holewall, ALLEGRO_BITMAP* floor, ALLEGRO_BITMAP* blood);

int losuj(int from, int to);