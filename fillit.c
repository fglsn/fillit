#include "libft/libft.h"
#include "fillit.h"
#include <fcntl.h>
#include <stdio.h> //remember forbidden lib!!

void	print_arr(char **content)
{
	int	y;

	y = 0;
	printf("\n");
	while (y < 4)
	{
		printf("%s\n", content[y]);
		y++;
	}
	printf("\n");
}

void	ft_arraydel(char **str_array, int size) // free all strings in 2d array and array itself
{
	int	i;
	
	i = 0;
	while (i < size)
	{
		ft_strdel(&str_array[i]);
		i++;
	}
	free(str_array);
}

char **parse_input_piece(char *buffer)
{
	int	i;
	char **input_piece;

	i = 0;
	input_piece = malloc(sizeof(char *) * 4);
	if (!input_piece)
		return (NULL);
	while (i < 4)
	{
		input_piece[i] = ft_strnew(4);
		if (!input_piece[i])
		{
			ft_arraydel(input_piece, i);
			return (NULL);
		}
		ft_memcpy(input_piece[i], &buffer[i * 5], 4);
		if (buffer[i * 5 + 4] != '\n')
		{
			ft_arraydel(input_piece, i + 1);
			return (NULL);
		}
		i++;
	}
	return (input_piece);
}

void	get_tetri_height(char **input_piece, int *ymin, int *ylen)
{
	int	y_min_coord;
	int	y_max;
	int y;
	int x;

	y_min_coord = 5;
	y_max = -1;
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (input_piece[y][x] == '#')
			{
				if (y < y_min_coord)
					y_min_coord = y;
				if (y > y_max)
					y_max = y;
			}
			x++;
		}
		y++;
	}
	*ymin = y_min_coord;
	*ylen = y_max - y_min_coord + 1;
	return ;
}

void	get_tetri_width(char **input_piece, int *xmin, int *xlen)
{
	int	x_min_coord;
	int	x_max;
	int y;
	int x;

	x_min_coord = 5;
	x_max = -1;
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (input_piece[y][x] == '#')
			{
				if (x < x_min_coord)
					x_min_coord = x;
				if (x > x_max)
					x_max = x;
			}
			x++;
		}
		y++;
	}
	*xmin = x_min_coord; //saving values straight to struct using pointers
	*xlen = x_max - x_min_coord + 1;
	return ;
}

t_piece	get_tetri_struct(char **input_piece, int count)
{
	char litera[26] = "ABCDEFGHIGKLMNOPQRSTUVWXYZ";
	t_piece tetrimino;

	tetrimino.content = input_piece;
	get_tetri_height(input_piece, &tetrimino.ymin, &tetrimino.ylen);
	get_tetri_width(input_piece, &tetrimino.xmin, &tetrimino.xlen);
	tetrimino.litera = litera[count];
	return (tetrimino);
}

int count_adjacence(char **input_piece, int x, int y)
{
	int	count_touches;

	count_touches = 0;
	if (y != 3 && input_piece[y + 1][x] == '#')
		count_touches++;
	if (y != 0 && input_piece[y - 1][x] == '#')
		count_touches++;
	if (x != 3 && input_piece[y][x + 1] == '#')
		count_touches++;
	if (x != 0 && input_piece[y][x - 1] == '#')
		count_touches++;
	return (count_touches);
}

int	check_tetrimino(char **input_piece, int count)
{
	int		x;
	int		y;
	int		count_touches;
	int		hash_count;

	y = 0;
	hash_count = 0;
	count_touches = 0;
	//printf("parse_tetrimino: hash_count %d, count_touches %d\n", hash_count, count_touches);
	while (y < 4) // counting touches and amount of hashes
	{
		x = 0;
		while (x < 4)
		{
			if (input_piece[y][x] == '#') // if # check top left right down coordinates, if # count++
			{
				count_touches = count_touches + count_adjacence(input_piece, x, y);
				hash_count++;
			}
			else if (input_piece[y][x] != '.')
				return (-1);
			x++;
		}
		y++;
	}
//	printf("parse_tetrimino: hash_count %d, count_touches %d\n", hash_count, count_touches);
	if (hash_count != 4 && (count_touches != 6 || count_touches != 8))
	{
		//ft_arraydel(input_piece, 4);
		return (-1);
	}
	return (1);
}

int	get_tetrimino(int fd, t_piece *tetrimino, int count) //string_array *input_piece == char ***input_piece
{
	int		read_ret;
	char	buffer[20];
	char	**input_piece;

	read_ret = read(fd, buffer, 20);
	if (read_ret != 20)
		return (-1);
	input_piece = parse_input_piece(buffer);
	if (!input_piece)
		return (-1);
	if (check_tetrimino(input_piece, count) == -1)
		return (-1);
	*tetrimino = get_tetri_struct(input_piece, count);
	return (1);
}

int	check_empty_line(int fd)
{
	int		read_ret;
	char	buffer[1];

	read_ret = read(fd, buffer, 1);
	if (read_ret < 0)
		return (-1);
	if (!read_ret)
		return (0);
	if (buffer[0] != '\n')
		return (-1);
	return (1);
}

int	get_tetriminos(int fd, t_piece *tetriminos) //we will count how many pieces we got. we will return 0 if error and return "error\n" in main then
{
	int		count;
	char	**input_piece; //array of lines with tetrimino
	int		valid_tet;
	int		continue_read;

	count = 0;
	continue_read = 1;
	while (continue_read) //we will read and save each piece at a time, unless there's nothing to read anymore or error (for example no \n after 4x4 block in input)
	{
		if (count > 26)
			return (-1);
		valid_tet = get_tetrimino(fd, &tetriminos[count], count);
		if (valid_tet == -1)
			return (-1);
		continue_read = check_empty_line(fd);
		if (continue_read < 0)
			return (-1);
		count++;
	}
	return (count);
}

void	set_content_to_null(t_piece *tetriminos)
{
	int	i;

	i = 0;
	while (i < 26)
	{
		tetriminos[i].content = NULL;
		i++;
	}
	return ;
}

void	free_content(t_piece *tetriminos)
{
	int	i;

	i = 0;
	while (i < 26)
	{
		if (tetriminos[i].content != NULL)
			ft_arraydel(tetriminos[i].content, 4);
		i++;
	}
	return ;
}

int	main(int argc, char **argv)
{
	int			fd;
	int			tet_count;
	t_piece	tetriminos[26];
	int	i = 0; //temp index

	if (argc != 2)
	{
		ft_putstr("usage: ./fillit sourse_file\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("error\n");
		return (1);
	}
	set_content_to_null(tetriminos);
	tet_count = get_tetriminos(fd, tetriminos);
	printf("Total tetrimio count: %d\n", tet_count);
	if (tet_count <= 0) // temp change from : <=
	{
		//free_content(tetriminos);
		ft_putstr("error\n");
		return (1);
	}
	while (i < tet_count) //temp check
	{
		print_arr(tetriminos[i].content);
		printf("xlen: %d\nylen: %d\nxmin: %d\nymin: %d\nlitera: %c\n", tetriminos[i].xlen, tetriminos[i].ylen,
				tetriminos[i].xmin, tetriminos[i].ymin, tetriminos[i].litera);
		i++;
	}
	return (0);
}