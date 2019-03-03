#include "init.h"

void must_init(bool test, const char *description)
{
	if (test) return;

	printf("couldn't initialize %s\n", description);
#ifdef _WIN32
	system("pause");
#endif
	exit(1);
}

void INIT()
{
	must_init(al_init(), "allegro");
	must_init(al_install_keyboard(), "keyboard");
	must_init(al_init_font_addon(),"font");
	must_init(al_init_ttf_addon(), "ttf");
	must_init(al_init_primitives_addon(), "primitives");
	must_init(al_init_image_addon(),"image");
}

void SETDISPLAY()
{
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
}

void MUSTINITandREGISTER(ALLEGRO_TIMER *timer, ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_DISPLAY *disp, ALLEGRO_FONT *font, ALLEGRO_TIMER *timertimer, ALLEGRO_BITMAP* shead, ALLEGRO_BITMAP* sbody, ALLEGRO_BITMAP* sturn, ALLEGRO_BITMAP* send, ALLEGRO_BITMAP* mouse, ALLEGRO_FONT *bigfont, ALLEGRO_FONT *smallfont, ALLEGRO_BITMAP* wall, ALLEGRO_BITMAP* holewall, ALLEGRO_BITMAP* floor, ALLEGRO_BITMAP* blood)
{
	must_init(timer, "timer");
	must_init(timertimer, "timertimer");
	must_init(queue, "queue");
	must_init(disp, "display");
	must_init(font, "font");
	must_init(shead, "shead");
	must_init(sbody, "sbody");
	must_init(sturn, "sturn");
	must_init(send, "send");
	must_init(mouse, "mouse");
	must_init(bigfont, "bigfont");
	must_init(smallfont, "smallfont");
	must_init(wall, "wall");
	must_init(holewall, "holewall");
	must_init(floor, "floor");
	must_init(blood, "blood");

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));
}

void DESTROY(ALLEGRO_TIMER *timer, ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_DISPLAY *disp, ALLEGRO_FONT *font, ALLEGRO_TIMER *timertimer, ALLEGRO_BITMAP* shead, ALLEGRO_BITMAP* sbody, ALLEGRO_BITMAP* sturn, ALLEGRO_BITMAP* send, ALLEGRO_BITMAP* mouse, ALLEGRO_FONT *bigfont, ALLEGRO_FONT *smallfont, ALLEGRO_BITMAP* wall, ALLEGRO_BITMAP* holewall, ALLEGRO_BITMAP* floor, ALLEGRO_BITMAP* blood)
{
	al_destroy_font(font);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_timer(timertimer);
	al_destroy_event_queue(queue);
	al_destroy_bitmap(shead);
	al_destroy_bitmap(sbody);
	al_destroy_bitmap(sturn);
	al_destroy_bitmap(send);
	al_destroy_bitmap(mouse);
	al_destroy_font(bigfont);
	al_destroy_font(smallfont);
	al_destroy_bitmap(wall);
	al_destroy_bitmap(holewall);
	al_destroy_bitmap(floor);
	al_destroy_bitmap(blood);
}

int losuj(int from, int to)
{
	return rand() % (to - from + 1) + from;
}