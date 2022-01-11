/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:30:08 by ishakuro          #+#    #+#             */
/*   Updated: 2022/01/11 13:20:13 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_piece
{
	char	**content;
	int		xlen;
	int		ylen;
	int		xmin;
	int		ymin;
	char	litera;
}				t_piece;

typedef struct s_board
{
	char	**board;
	int		size;
}				t_board;

int		open_file(char *filename);
void	set_content_to_null(t_piece *tetriminos);
void	free_content(t_piece *tetriminos);
int		put_error(t_piece *tetriminos);

int		get_tetriminos(int fd, t_piece *tetriminos);
int		get_tetrimino(int fd, t_piece *tetrimino, int count);
char	**parse_input_piece(char *buffer);
int		should_read_further(int fd);
void	ft_arraydel(char **str_array, int size);

int		check_tetrimino(char **input_piece);
int		count_adjacence(char **input_piece, int x, int y);
int		check_format(char **input_piece, int hash_num, int touches);

t_piece	get_struct(char **input_piece, int count);
void	get_tetri_width(char **input_piece, int *xmin, int *xlen);
void	get_tetri_height(char **input_piece, int *ymin, int *ylen);
void	update_min_max(char element, int n, int *n_min, int *n_max);

int		solver(t_piece *tetriminos, int tet_count);
int		try_to_solve(t_board *board, t_piece *tetriminos, int tet_count, int i);
int		insert_tetri(t_board *board, int x, int y, t_piece *tetri);
int		validate_place(t_board *board, int x, int y, t_piece *tetri);
void	remove_tetri(t_board *board, int x, int y, t_piece *tetri);

size_t	get_min_board_size(int tet_count);
int		initialize_board(size_t board_size, t_board *board);
void	draw_board(t_board *board);

#endif
