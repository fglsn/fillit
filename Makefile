CC = clang
FLAGS = -Wall -Wextra -Werror

all: clean
	make main
	
main:
	$(CC) $(FLAGS) *.c *.h libft/libft.a

clean:
	rm -f *.o *.a *.gch *.out libft/*.o

fclean: clean
	rm -rf

re: fclean all


#leaks -atExit -- ./a.out test.txt