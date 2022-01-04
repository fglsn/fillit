#include "libft/libft.h"
#include "fillit.h"
#include <fcntl.h>

void	ft_arraydel(char **str_array, int size) // free all strings in 2d array and array itself
{
	int	i;
	
	i = 0;
	while (i++ < size)
	{
		ft_strdel(&str_array[i]);
	}
	free(str_array);
}

int	check_line(char *line)
{
	while (*line)
	{
		if (*line != '.' && *line != '#')
			return (0);
		line++;
	}
	return (1);
}

// If input file invalid, free what was saved previousely and return null to get_tetriminos function
// If all good save lines into 4x4 arrays 
char	**check_input_format(int fd)
{
	int		i;
	int		gnl;
	char	**lines;

	lines = malloc(sizeof(char*) * 4);
	if (!lines)
		return (NULL);
	i = 0;
	while (i++ < 4)
	{
		gnl = ft_get_next_line(fd, &lines[i]); //reading line by line and saving into tetri-input to 4x4 array, return lines to get tetriminos function
		if (gnl < 0)  //free allocated array of pointers if gnl returned error 
		{
			ft_arraydel(&lines, 4);
			return (NULL);
		}
		if (ft_strlen(lines[i]) != 4 && !check_line(line[i])) // free if line not 4p long or has something instead of . or #
		{
			ft_arraydel(&lines, 4);
			return (NULL);
		}
	}
	return (lines);
}


//this function checks if there is a \n after 4x4 tetri block and if this line is empty and also tells us if everything was read, end of file
int	check_empty_line(int fd) 
{
	char	*line;
	int		res;
	int		line_length;
	
	res = ft_get_next_line(fd, &line);
	if (res == -1) // means no '\n' after 4x4 block or error from gnl. so error
	{
		free(line);
		return (-1);
	}
	if (strlen(line)) //error if last line not empty
	{
		res = -1;
	}
	free(line);
	return (res); //returns 0 if all read, 1 if not end of file, -1 if error
}

// not finished. with help of this function we will check if tetri is valid
// alighn to topleft corner and save result to array of structs. one parsed tetri == one struct 
t_piece	parse_tetrimino(char **input_piece) 
{
	int		x;
	int		y;
	int		count_touches;
	int		hash_count;
	t_piece	tetri_block;

	y = 0;
	hash_count = 0;
	count_touches = 0;
	while (y < 4) // counting touches and amount of hashes
	{
		x = 0;
		while (x < 4)
		{
			if (input_piece[y][x] == '#') // if # check top left right down coordinates, if # count++
			{
				if (y != 3 && input_piece[y + 1][x] == '#')
					count_touches++;
				if (y != 0 && input_piece[y - 1][x] == '#')
					count_touches++;
				if (x != 3 && input_piece[y][x + 1] == '#')
					count_touches++;
				if (x != 0 && input_piece[y][x - 1] == '#')
					count_touches++;
				hash_count++;
			}
			x++;
		}
		y++;
	}
	if (hash_count != 4 && count_touches < 6)
	{
		ft_arraydel(input_piece);
		return (NULL);
	}
	// todo : calculate width and height of piece, save to struct and we are ready to solve
}

int	get_tetriminos(int fd, t_piece *tetriminos) //we will count how many pieces we got. we will return 0 if error and return "error\n" in main then
{
	int		i;
	int		count;
	char	**input_piece; //array of lines with tetrimino

	i = 0;
	count = 0;
	while (check_empty_line(fd) > 0) //we will read and save each piece at a time, unless there's nothing to read anymore or error (for example no \n after 4x4 block in input)
	{
		input_piece = check_input_format(fd);
		if (!input_piece)
			return (0);
		if (!parse_tetrimino(input_piece)) //not finished. with help of this function we will check if tetri is valid, alighn to topleft corner and save result to array of structs. one parsed tetri == one struct
			return (0);
		count++; 
	}
	return (count);
}

int	main(int argc, char **argv)
{
	int			fd;
	int			tet_count;
	t_piece	tetriminos[26];

	if (argc != 2)
	{
		ft_putstr("usage: ./fillit sourse_file\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	tet_count = get_tetriminos(fd, tetriminos);
	if (tet_count <= 0 || tet_count > 26)
	{
		ft_putstr("error\n");
		return (1);
	}
}