#include "snake.h"
#include "init.h"

snake *sinit(float x, float y, int kierunek, int tab[][200])
{
	snake* ptr;
	ptr = (snake*)malloc(sizeof(snake));
	snake_elem* elem_ptr;
	elem_ptr = (snake_elem*)malloc(sizeof(snake_elem)); //glowa
	elem_ptr->x = x;
	elem_ptr->y = y;
	elem_ptr->direction = kierunek;
	elem_ptr->last = 0;
	elem_ptr->next = NULL;
	ptr->head = elem_ptr;

	elem_ptr = (snake_elem*)malloc(sizeof(snake_elem)); //ogon
	elem_ptr->x = x - SKOK;
	elem_ptr->y = y;
	elem_ptr->direction = kierunek;
	elem_ptr->last = kierunek;
	elem_ptr->next = ptr->head;
	ptr->last = elem_ptr;

	int tabx = x/SKOK, taby = y/SKOK;

	tab[tabx][taby] = WAZ;
	tab[tabx-1][taby] = WAZ;

	return ptr;
}

void przesun(snake* ptr, int kierunek, int tab[][200], int width, bool *wallcollision)
{
	float x = ptr->head->x;
	float y = ptr->head->y;
	
	switch (kierunek)
	{
	case GORA:
		y -= SKOK;
		break;
	case DOL:
		y += SKOK;
		break;
	case LEWO:
		x -= SKOK;
		break;
	case PRAWO:
		x += SKOK;
		break;
	}

	if (x >= width)
		x = 0;
	else if (x < 0)
		x = width - SKOK;

	int tabx = (ptr->last->x) / SKOK, taby = (ptr->last->y) / SKOK; //usuniecie ogona
	tab[tabx][taby] = PUSTEPOLE;
	ptr->last->x = x;
	ptr->last->y = y;
	ptr->last->last = 0;
	ptr->last->direction = kierunek;

	tabx = x / SKOK; taby = y / SKOK; //dodanie glowy

	if (tab[tabx][taby] == SCIANA)
		*wallcollision = true;
	else
		*wallcollision = false;

	tab[tabx][taby] = WAZ;

	if (ptr->last->next != NULL)
	{
		snake_elem* elem_ptr = ptr->last;
		ptr->last = ptr->last->next;
		ptr->head->last = kierunek;
		ptr->head->next = elem_ptr;
		ptr->head = elem_ptr;
		ptr->head->next = NULL;
	}
}

void dodaj(snake* ptr, int kierunek, int tab[][200])
{
	float x = ptr->head->x;
	float y = ptr->head->y;
	switch (kierunek)
	{
	case GORA:
		y -= SKOK;
		break;
	case DOL:
		y += SKOK;
		break;
	case LEWO:
		x -= SKOK;
		break;
	case PRAWO:
		x += SKOK;
		break;
	}

	int tabx = x / SKOK, taby = y / SKOK;
	tab[tabx][taby] = WAZ;

	snake_elem* elem_ptr;
	elem_ptr = (snake_elem*)malloc(sizeof(snake_elem));
	elem_ptr->x = x;
	elem_ptr->y = y;
	elem_ptr->direction = kierunek;
	elem_ptr->next = NULL;
	ptr->head->next = elem_ptr;
	ptr->head->last = kierunek;
	ptr->head = elem_ptr;
}

bool checkapple(snake* ptr, int last, int tab[][200])
{
	int nx = (ptr->head->x) / SKOK;
	int ny = (ptr->head->y) / SKOK;

	switch (last)
	{
	case GORA:
		return tab[nx][ny - 1] == JABLKO;
		break;
	case DOL:
		return tab[nx][ny + 1] == JABLKO;
		break;
	case PRAWO:
		return tab[nx + 1][ny] == JABLKO;
		break;
	case LEWO:
		return tab[nx - 1][ny] == JABLKO;
		break;
	}
	return false;
}

bool checkcollision(snake *ptr, int last, int tab[][200])
{
	int nx = (ptr->head->x) / SKOK;
	int ny = (ptr->head->y) / SKOK;
	int lastnx = (ptr->last->x) / SKOK;
	int lastny = (ptr->last->y) / SKOK;

	switch (last) // NASTEPNA POZYCJA JEST ŒCIAN¥ LUB (JEST WÊ¯EM, TAKIM ¯E (NIE JEST TO OGON))
	{
	case GORA:
		return (tab[nx][ny - 1] == SCIANA || (tab[nx][ny-1] == WAZ && ( nx!=lastnx || (ny - 1)!=lastny ) ) );
		break;
	case DOL:
		return (tab[nx][ny + 1] == SCIANA || (tab[nx][ny + 1] == WAZ && ( nx != lastnx || (ny + 1) != lastny ) ) );
		break;
	case PRAWO:
		return (tab[nx + 1][ny] == SCIANA || (tab[nx + 1][ny] == WAZ && ( (nx + 1) != lastnx || ny != lastny ) ) );
		break;
	case LEWO:
		return (tab[nx - 1][ny] == SCIANA || (tab[nx - 1][ny] == WAZ && ( (nx - 1) != lastnx || ny != lastny ) ) );
		break;
	}
	return false;
}