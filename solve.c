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
	return (1);
}
