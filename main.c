#include "libft/libft.h"
#include "fillit.h"
#include <fcntl.h>

static void	ft_arraydel(char **str_array, int size)
{
	int	i;
	
	i = 0;
	while (i++ < size)
	{
		ft_strdel(&str_array[i]);
	}
	free(str_array);
}

static int	check_line(char *line)
{
	while (*line)
	{
		if (*line != '.' && *line != '#')
			return (0);
		line++;
	}
	return (1);
}

static char	**check_input_format(int fd)
{
	int		i;
	int		gnl;
	char	**lines;

	lines = malloc(sizeof(char*) * 4);
	if (!lines)
		return (NULL);
	i = 0;
	while (i++ < 4)
	{
		gnl = ft_get_next_line(fd, &lines[i]);
		if (gnl < 0)
		{
			ft_arraydel(&lines, 4);
			return (NULL);
		}
		if (ft_strlen(lines[i]) != 4 && !check_line(line[i]))
		{
			ft_arraydel(&lines, 4);
			return (NULL);
		}
	}
	return (lines);
}

static int	check_empty_line(int fd)
{
	char	*line;
	int		res;
	int		line_length;
	
	res = ft_get_next_line(fd, &line);
	if (res == -1) // means no '\n' after 4x4 block or error from gnl. so error
	{
		free(line);
		return (-1);
	}
	if (strlen(line)) //error if last line not empty
	{
		res = -1;
	}
	free(line);
	return (res); //returns 0 if all read, 1 if not end of file, -1 if error
}

static t_piece	parse_tetrimino(char **input_piece)
{
	int		x;
	int		y;
	int		count_touches;
	int		hash_count;
	t_piece	tetri_block;

	y = 0;
	hash_count = 0;
	count_touches = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (input_piece[y][x] == '#')
			{
				if (y != 3 && input_piece[y + 1][x] == '#')
					count_touches++;
				if (y != 0 && input_piece[y - 1][x] == '#')
					count_touches++;
				if (x != 3 && input_piece[y][x + 1] == '#')
					count_touches++;
				if (x != 0 && input_piece[y][x - 1] == '#')
					count_touches++;
				hash_count++;
			}
			x++;
		}
		y++;
	}
	if (hash_count != 4 && count_touches < 6)
	{
		ft_arraydel(input_piece);
		return (NULL);
	}
	
}

static int	get_tetriminos(int fd, t_piece *tetriminos)
{
	int		i;
	int		count;
	char	**input_piece;

	i = 0;
	count = 0;
	while (check_empty_line(fd) > 0)
	{
		input_piece = check_input_format(fd, &check_ret_val);
		if (!input_piece)
			return (0);
		if (parse_tetrimino())
		
	}
	return (count);
}

int	main(int argc, char **argv)
{
	int			fd;
	int			tet_count;
	t_piece	tetriminos[26];

	if (argc != 2)
	{
		ft_putstr("usage: ./fillit sourse_file\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	tet_count = get_tetriminos(fd, tetriminos);
	if (tet_count <= 0 || tet_count > 26)
	{
		ft_putstr("error\n");
		return (1);
	}
}