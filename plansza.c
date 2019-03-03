#include "init.h"
#include "plansza.h"
#include "snake.h"

void initplansza(int tab[][200], int width, int height)
{
	int nwidth = width / SKOK, nheight = height / SKOK;
	
	for (int i = 1; i < nheight; i++)
	{
		for (int j = 0; j < nwidth; j++)
		{
			if (i == 1 || i + 1 == nheight || j == 0 || j + 1 == nwidth)
				tab[j][i] = SCIANA;
		}
	}

	if (width == 640)
	{
		for (int i = 5; i < 8; i++)
		{
			tab[0][i] = PUSTEPOLE;
			tab[nwidth - 1][i] = PUSTEPOLE;
		}
	}
	else if (width == 840)
	{
		for (int i = 7; i <= 10; i++)
		{
			tab[0][i] = PUSTEPOLE;
			tab[nwidth - 1][i] = PUSTEPOLE;
		}
	}
	else
	{
		for (int i = 5; i <= 7; i++)
		{
			tab[0][i] = PUSTEPOLE;
			tab[0][i+10] = PUSTEPOLE;
			tab[nwidth - 1][i] = PUSTEPOLE;
			tab[nwidth - 1][i+10] = PUSTEPOLE;
		}
	}
}