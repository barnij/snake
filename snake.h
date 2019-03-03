#include <stdbool.h>

typedef struct snake_elem {
	float x, y;
	int direction;
	int last;
	struct snake_elem* next;
}snake_elem;

typedef struct snake {
	struct snake_elem* head;
	struct snake_elem* last;
}snake;

enum kierunek { LEWO = 82, PRAWO, GORA, DOL };

enum typkafelka { PUSTEPOLE = 0 , WAZ, JABLKO, SCIANA};

snake *sinit(float x, float y, int kierunek, int tab[][200]);
void przesun(snake* ptr, int kierunek, int tab[][200], int width, bool *wallcollision);
void dodaj(snake* ptr, int kierunek, int tab[][200]);
bool checkapple(snake* ptr, int last, int tab[][200]);
bool checkcollision(snake *ptr, int last, int tab[][200]);