#include "fillit.h"
#include <stdio.h>

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
	size_t		i;

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

int	validate_place(t_board *board, int x, int y, t_piece *tetri)
{
	int	iy;
	int	ix;
	int	ylen;
	int	xlen;

	iy = 0;
	ylen = tetri->ylen;
	xlen = tetri->xlen;
	if (y + ylen >= board->size || x + xlen >= board->size)
		return (0);
	while (iy < ylen)
	{
		ix = 0;
		while (ix < xlen)
		{
			printf("%d %d\n", ix, iy);
			if (board->board[y + iy][x + ix] != '.' && tetri->content[tetri->ymin + iy][tetri->xmin + ix] == '#')
			{
				return (0);
			}
			ix++;
		}
		iy++;
	}
	return (1);
}

int	insert_tetri(t_board *board, int x, int y, t_piece *tetri)
{
	int	iy;
	int	ix;
	int	ylen;
	int	xlen;

	iy = 0;
	ylen = tetri->ylen;
	xlen = tetri->xlen;
	if (!validate_place(board, x, y, tetri))
		return (0);
	while (iy < ylen)
	{
		ix = 0;
		while (ix < xlen)
		{
			if (board->board[y + iy][x + ix] == '.' \
				&& tetri->content[tetri->ymin + iy][tetri->xmin + ix] == '#')
				board->board[y + iy][x + ix] = tetri->litera;
			ix++;
		}
		iy++;
	}
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

void	test_draw(t_piece *tetri, int tet_count)
{
	size_t	board_size;
	t_board	board;

	board_size = get_min_board_size(tet_count);
	if (!initialize_board(board_size, &board))
	{
		printf("Failed to initialize\n");
	}
	if (!insert_tetri(&board, 2, 2, tetri))
	{
		printf("Failed to insert\n");
	}
	draw_board(&board);
	ft_arraydel(board.board, board_size);
}
