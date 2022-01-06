#include "libft/libft.h"
#include "fillit.h"
#include <fcntl.h>
#include <stdio.h>

void	print_arr(char **content)
{
	int	y;

	y = 0;
	printf("\n");
	while (y < 4)
	{
		printf("%s\n", content[y]);
		y++;
	}
	printf("\n");
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

int	main(int argc, char **argv)
{
	int			fd;
	int			tet_count;
	t_piece		tetriminos[26];
	int	i = 0; //temp index
	if (argc != 2)
	{
		ft_putstr("usage: ./fillit sourse_file\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("error\n");
		return (1);
	}
	set_content_to_null(tetriminos);
	tet_count = get_tetriminos(fd, tetriminos);
	printf("Total tetrimio count: %d\n", tet_count);
	if (tet_count <= 0)
	{
		free_content(tetriminos);
		ft_putstr("error\n");
		return (1);
	}
	while (i < tet_count)
	{
		print_arr(tetriminos[i].content);
		printf("xlen: %d\nylen: %d\nxmin: %d\nymin: %d\nlitera: %c\n", tetriminos[i].xlen, tetriminos[i].ylen,
				tetriminos[i].xmin, tetriminos[i].ymin, tetriminos[i].litera);
		i++;
	}
	free_content(tetriminos);
	return (0);
}
