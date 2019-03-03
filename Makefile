CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror
LFLAGS = `pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_ttf-5 allegro_color-5 allegro_video-5 allegro_primitives-5 --libs --cflags`

NAME = snake
SRC = main.c init.c game.c startmenu.c plansza.c snake.c
DEPS = init.h game.h startmenu.h plansza.h snake.h
OBJS = main.o init.o game.o startmenu.o plansza.o snake.o

YOU :$(SRC) $(NAME)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)
	
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<
	
clean:
	rm -f $(OBJS) $(NAME)