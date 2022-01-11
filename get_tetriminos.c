/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tetriminos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:55:43 by ishakuro          #+#    #+#             */
/*   Updated: 2022/01/11 13:17:47 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	get_tetriminos(int fd, t_piece *tetriminos)
{
	int		count;
	int		valid_tet;
	int		continue_read;

	count = 0;
	continue_read = 1;
	while (continue_read)
	{
		if (count > 26)
			return (-1);
		valid_tet = get_tetrimino(fd, &tetriminos[count], count);
		if (valid_tet == -1)
			return (-1);
		continue_read = should_read_further(fd);
		if (continue_read < 0)
			return (-1);
		count++;
	}
	return (count);
}

int	get_tetrimino(int fd, t_piece *tetrimino, int count)
{
	int		read_ret;
	char	buffer[20];
	char	**input_piece;

	read_ret = read(fd, buffer, 20);
	if (read_ret != 20)
		return (-1);
	input_piece = parse_input_piece(buffer);
	if (!input_piece)
		return (-1);
	if (check_tetrimino(input_piece) == -1)
	{
		ft_arraydel(input_piece, 4);
		return (-1);
	}
	*tetrimino = get_struct(input_piece, count);
	return (1);
}

char	**parse_input_piece(char *buffer)
{
	int		i;
	char	**input_piece;

	i = 0;
	input_piece = malloc(sizeof(char *) * 4);
	if (!input_piece)
		return (NULL);
	while (i < 4)
	{
		input_piece[i] = ft_strnew(4);
		if (!input_piece[i])
		{
			ft_arraydel(input_piece, i);
			return (NULL);
		}
		ft_memcpy(input_piece[i], &buffer[i * 5], 4);
		if (buffer[i * 5 + 4] != '\n')
		{
			ft_arraydel(input_piece, i + 1);
			return (NULL);
		}
		i++;
	}
	return (input_piece);
}

int	should_read_further(int fd)
{
	int		read_ret;
	char	buffer[1];

	read_ret = read(fd, buffer, 1);
	if (read_ret < 0)
		return (-1);
	if (!read_ret)
		return (0);
	if (buffer[0] != '\n')
		return (-1);
	return (1);
}

void	ft_arraydel(char **str_array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_strdel(&str_array[i]);
		i++;
	}
	free(str_array);
}
