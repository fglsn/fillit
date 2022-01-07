/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:30:08 by ishakuro          #+#    #+#             */
/*   Updated: 2022/01/07 14:45:48 by ishakuro         ###   ########.fr       */
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

void	test_draw(t_piece *tetri, int tet_count);

int		get_tetriminos(int fd, t_piece *tetriminos);
int		check_empty_line(int fd);
int		get_tetrimino(int fd, t_piece *tetrimino, int count);
t_piece	get_tetri_struct(char **input_piece, int count);
char	**parse_input_piece(char *buffer);

int		check_tetrimino(char **input_piece);
int		count_adjacence(char **input_piece, int x, int y);
void	get_tetri_width(char **input_piece, int *xmin, int *xlen);
void	get_tetri_height(char **input_piece, int *ymin, int *ylen);

void	ft_arraydel(char **str_array, int size);

#endif
