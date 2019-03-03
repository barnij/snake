#include "init.h"
#include "snake.h"
#include "startmenu.h"
#include "plansza.h"
#include "game.h"

int main()
{	
	INIT();
	SETDISPLAY();
	int width = 640, height = 480, speed = 4;
	bool restart = false;

	while (1)
	{
		if(!restart)
			startmenu(&width, &height, &speed);
		startgame(width,height,speed,&restart);
	}

	return 0;
}