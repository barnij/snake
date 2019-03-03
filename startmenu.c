#include "init.h"
#include "startmenu.h"

void startmenu(int *w, int *h, int *s)
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
	int width, height, speed;

	bool wyborokna = true;
	while (wyborokna)
	{
		int nrrozmiar = 0;
		printf("Bartosz Jaskiewicz - projekt z przedmiotu \n\"Wstep do programowania w jezyku C\"\n\n");
		printf("Witamy w konfiguratorze gry Snake!\n\n");
		printf("Wybierz wielkosc planszy:\n");
		printf("1) Mala (640px/480px)\n"); //16 12
		printf("2) Srednia (840px/680px)\n"); //21 17
		printf("3) Duza (1200px/880px)\n"); //30 22
		printf("0) Wyjscie\n\nWybrana opcja: ");
#ifdef _WIN32
		scanf_s("%d", &nrrozmiar);
#endif
#ifdef __unix__
		scanf("%d", &nrrozmiar);
#endif

		switch (nrrozmiar)
		{
		case 1:
			width = 640; height = 480;
			wyborokna = false;
			break;
		case 2:
			width = 840; height = 680;
			wyborokna = false;
			break;
		case 3:
			width = 1200; height = 880;
			wyborokna = false;
			break;
		case 0:
			printf("\nDo widzenia!\n");
#ifdef _WIN32
			Sleep(1000);
#endif
#ifdef __unix__
			sleep(1);
#endif
			exit(0);
			break;
		default:
#ifdef _WIN32
			system("cls");
#else
			system("clear");
#endif
			break;
		}
	}

	wyborokna = true;

	while (wyborokna)
	{
#ifdef _WIN32
		system("cls");
#endif
#ifdef __unix__
		system("clear");
#endif
		int nrszybkosc = 0;
		printf("Dobrze.\n Teraz wybierz poziom trudnosci:\n\n");
		printf("1) Slimak\n"); //7
		printf("2) Wonsz\n"); //4
		printf("3) Pytong\n"); //1
		printf("0) Wyjscie\n\nWybrana opcja: ");
#ifdef _WIN32
		scanf_s("%d", &nrszybkosc);
#endif
#ifdef __unix__
		scanf("%d", &nrszybkosc);
#endif

		switch (nrszybkosc)
		{
		case 1:
			speed = 7;
			wyborokna = false;
			break;
		case 2:
			speed = 4;
			wyborokna = false;
			break;
		case 3:
			speed = 1;
			wyborokna = false;
			break;
		case 0:
			printf("\nDo widzenia!\n");
#ifdef _WIN32
			Sleep(1000);
#endif
#ifdef __unix__
			sleep(1);
#endif
			exit(0);
			break;
		default:
#ifdef _WIN32
			system("cls");
#endif
#ifdef __unix__
			system("clear");
#endif
			break;
		}
	}

	*h = height; *w = width, *s = speed;
}