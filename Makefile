NAME = so_long
FLAGS = -Wall -Wextra -Werror
SOURCES = main.c map1.c map2.c map3.c window1.c window2.c hooks1.c hooks2.c
OBJECTS = $(SOURCES:.c=.o)
BONUS_SOURCES = $(SOURCES:.c=_bonus.c) window3_bonus.c hooks3_bonus.c
BONUS_OBJECTS = $(BONUS_SOURCES:.c=.o)

all : $(NAME)

$(NAME) : libmlx42.a libft/libft.a $(OBJECTS)
	gcc $(OBJECTS) -g -L. -lmlx42 -lglfw  -Llibft -lft -o $(NAME)

bonus : libmlx42.a libft/libft.a $(BONUS_OBJECTS)
	gcc $(BONUS_OBJECTS) -g -L. -lmlx42 -lglfw  -Llibft -lft -o $(NAME)

libft/libft.a :
	cd libft; make libft.a; make clean

libmlx42.a :
	git clone https://github.com/codam-coding-college/MLX42.git
	cd MLX42; cmake -B build; cmake --build build -j4
	mv MLX42/build/libmlx42.a .
	mv MLX42/include/MLX42/MLX42.h .
	rm -rf MLX42

%.o : %.c 
	gcc $(FLAGS) -g -c $<

clean :
	rm -f $(OBJECTS) $(BONUS_OBJECTS)

fclean : clean
	rm -f $(NAME)
	rm -rf MLX42
	rm MLX42.h
	rm libmlx42.a 

re : fclean all
