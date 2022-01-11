/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:21:05 by ishakuro          #+#    #+#             */
/*   Updated: 2022/01/11 15:01:05 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

size_t	get_min_board_size(int tet_count)
{
	int		num_hashes;
	int		size;

	size = 1;
	num_hashes = tet_count * 4;
	while (size * size < num_hashes)
	{
		size++;
	}
	return (size);
}

int	initialize_board(size_t board_size, t_board *board)
{
	char	**board_content;
	size_t	i;

	i = 0;
	board_content = malloc(sizeof(char *) * board_size);
	if (!board_content)
		return (0);
	while (i < board_size)
	{
		board_content[i] = ft_strnew((size_t)board_size);
		if (!board_content[i])
		{
			ft_arraydel(board_content, i);
			return (0);
		}
		ft_memset(board_content[i], '.', board_size);
		i++;
	}
	board->board = board_content;
	board->size = board_size;
	return (1);
}

void	draw_board(t_board *board)
{
	int	i;

	i = 0;
	while (i < board->size)
	{
		ft_putstr(board->board[i]);
		ft_putchar('\n');
		i++;
	}
}
