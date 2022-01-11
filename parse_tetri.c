/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tetri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:20:28 by ishakuro          #+#    #+#             */
/*   Updated: 2022/01/11 11:27:00 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	check_lines_format(char **input_piece, int hash_num, int touches)
{
	int		x;
	int		y;

	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (input_piece[y][x] != '#' && input_piece[y][x] != '.')
				return (0);
			if (hash_num != 4 || (touches != 6 && touches != 8))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
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
			x++;
		}
		y++;
	}
	if (!check_lines_format(input_piece, hash_count, count))
		return (-1);
	return (1);
}
