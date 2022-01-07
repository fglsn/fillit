#include "fillit.h"

void	update_min_max(char element, int n, int *n_min, int *n_max)
{
	if (element == '#')
	{
		if (n < *n_min)
			*n_min = n;
		if (n > *n_max)
			*n_max = n;
	}
}

void	get_tetri_height(char **input_piece, int *ymin, int *ylen)
{
	int	y_max;
	int	y;
	int	x;

	*ymin = 5;
	y_max = -1;
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			update_min_max(input_piece[y][x], y, ymin, &y_max);
			x++;
		}
		y++;
	}
	*ylen = y_max - *ymin + 1;
}

void	get_tetri_width(char **input_piece, int *xmin, int *xlen)
{
	int	x_max;
	int	y;
	int	x;

	*xmin = 5;
	x_max = -1;
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			update_min_max(input_piece[y][x], x, xmin, &x_max);
			x++;
		}
		y++;
	}
	*xlen = x_max - *xmin + 1;
}

int	count_adjacence(char **input_piece, int x, int y)
{
	int	count;

	count = 0;
	if (y != 3 && input_piece[y + 1][x] == '#')
		count++;
	if (y != 0 && input_piece[y - 1][x] == '#')
		count++;
	if (x != 3 && input_piece[y][x + 1] == '#')
		count++;
	if (x != 0 && input_piece[y][x - 1] == '#')
		count++;
	return (count);
}

int	check_tetrimino(char **input_piece)
{
	int		x;
	int		y;
	int		count;
	int		hash_count;

	y = 0;
	hash_count = 0;
	count = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (input_piece[y][x] == '#')
			{
				count = count + count_adjacence(input_piece, x, y);
				hash_count++;
			}
			else if (input_piece[y][x] != '.')
				return (-1);
			x++;
		}
		y++;
	}
	if (hash_count != 4 && (count != 6 && count != 8))
		return (-1);
	return (1);
}
