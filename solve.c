/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:20:47 by ishakuro          #+#    #+#             */
/*   Updated: 2022/01/11 11:20:57 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	remove_tetri(t_board *board, int x, int y, t_piece *tetri)
{
	int	iy;
	int	ix;
	int	ylen;
	int	xlen;

	iy = 0;
	ylen = tetri->ylen;
	xlen = tetri->xlen;
	while (iy < ylen)
	{
		ix = 0;
		while (ix < xlen)
		{
			if (board->board[y + iy][x + ix] == tetri->litera)
				board->board[y + iy][x + ix] = '.';
			ix++;
		}
		iy++;
	}
}

int	try_to_solve(t_board *board, t_piece *tetriminos, int tet_count, int i)
{
	int	x;
	int	y;
	int	was_inserted;

	y = 0;
	while (y < board->size)
	{
		x = 0;
		while (x < board->size)
		{
			was_inserted = insert_tetri(board, x, y, &tetriminos[i]);
			if (was_inserted && i == tet_count - 1)
				return (1);
			else if (was_inserted)
			{
				if (try_to_solve(board, tetriminos, tet_count, i + 1))
					return (1);
				else
					remove_tetri(board, x, y, &tetriminos[i]);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	solve(t_piece *tetriminos, int tet_count)
{
	int		board_size;
	t_board	board;

	board_size = get_min_board_size(tet_count);
	while (1)
	{
		if (!initialize_board(board_size, &board))
			return (0);
		if (try_to_solve(&board, tetriminos, tet_count, 0))
		{
			draw_board(&board);
			ft_arraydel(board.board, board_size);
			return (1);
		}
		ft_arraydel(board.board, board_size);
		board_size++;
	}
}
