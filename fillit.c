/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:56:01 by ishakuro          #+#    #+#             */
/*   Updated: 2022/01/11 11:31:53 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	set_content_to_null(t_piece *tetriminos)
{
	int	i;

	i = 0;
	while (i < 26)
	{
		tetriminos[i].content = NULL;
		i++;
	}
	return ;
}

void	free_content(t_piece *tetriminos)
{
	int	i;

	i = 0;
	while (i < 26)
	{
		if (tetriminos[i].content != NULL)
			ft_arraydel(tetriminos[i].content, 4);
		i++;
	}
	return ;
}

int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("error\n");
		return (0);
	}
	return (fd);
}

int	put_error(t_piece *tetriminos)
{
	free_content(tetriminos);
	ft_putstr("error\n");
	return (1);
}

int	main(int argc, char **argv)
{
	int			fd;
	int			tet_count;
	t_piece		tetriminos[26];

	if (argc != 2)
	{
		ft_putstr("usage: ./fillit sourse_file\n");
		return (1);
	}
	fd = open_file(argv[1]);
	if (!fd)
		return (1);
	set_content_to_null(tetriminos);
	tet_count = get_tetriminos(fd, tetriminos);
	if (tet_count <= 0)
		return (put_error(tetriminos));
	if (!solve(tetriminos, tet_count))
		return (put_error(tetriminos));
	free_content(tetriminos);
	return (0);
}
