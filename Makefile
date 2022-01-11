FLAGS = -Wall -Wextra -Werror
NAME = fillit
FILES = fillit.c get_tetri.c parse_tetri.c prepare_board.c solve.c helpers.c
HEADER = fillit.h
LIBFT = libft/

$(NAME):
	make -C $(LIBFT)
	clang $(FLAGS) -o $(NAME) $(FILES) -I $(HEADER) -L. libft/libft.a

all: $(NAME)

clean:
	rm -f *.o *.gch *.out libft/*.o libft/*.a

fclean: clean
	rm -rf fillit

re: fclean all


#leaks -atExit -- ./fillit max.txt