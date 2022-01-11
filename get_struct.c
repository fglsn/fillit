/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:55:25 by ishakuro          #+#    #+#             */
/*   Updated: 2022/01/11 13:15:16 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_piece	get_struct(char **input_piece, int count)
{
	t_piece	tetrimino;

	tetrimino.content = input_piece;
	get_tetri_height(input_piece, &tetrimino.ymin, &tetrimino.ylen);
	get_tetri_width(input_piece, &tetrimino.xmin, &tetrimino.xlen);
	tetrimino.litera = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[count];
	return (tetrimino);
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
