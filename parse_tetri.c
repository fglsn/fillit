#include "fillit.h"

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
