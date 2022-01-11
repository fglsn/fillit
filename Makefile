FLAGS = -Wall -Wextra -Werror
NAME = fillit
SRC = main.c get_tetriminos.c check_tetrimino.c get_struct.c board.c solver.c 
OBJECTS = $(SRC:.c=.o)
HEADER = fillit.h
LIBFT = libft/

all: $(NAME)

$(NAME):
	make -C $(LIBFT)
	clang $(FLAGS) -o $(NAME) $(SRC) -I $(HEADER) -L. libft/libft.a

clean:
	/bin/rm -f $(OBJECTS)
	make -C $(LIBFT) clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C $(LIBFT) fclean

re: fclean all

#leaks -atExit -- ./fillit