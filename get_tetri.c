#include "fillit.h"

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

t_piece	get_tetri_struct(char **input_piece, int count)
{
	char	litera[26];
	t_piece	tetrimino;

	litera = "ABCDEFGHIGKLMNOPQRSTUVWXYZ";
	tetrimino.content = input_piece;
	get_tetri_height(input_piece, &tetrimino.ymin, &tetrimino.ylen);
	get_tetri_width(input_piece, &tetrimino.xmin, &tetrimino.xlen);
	tetrimino.litera = litera[count];
	return (tetrimino);
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
	if (check_tetrimino(input_piece, count) == -1)
		return (-1);
	*tetrimino = get_tetri_struct(input_piece, count);
	return (1);
}

int	check_empty_line(int fd)
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

int	get_tetriminos(int fd, t_piece *tetriminos)
{
	int		count;
	char	**input_piece;
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
		continue_read = check_empty_line(fd);
		if (continue_read < 0)
			return (-1);
		count++;
	}
	return (count);
}
