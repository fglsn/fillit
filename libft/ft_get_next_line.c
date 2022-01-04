/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:39:36 by ishakuro          #+#    #+#             */
/*   Updated: 2022/01/03 15:45:34 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	join_and_free(char **s1, char *s2)
{
	char	*temp;

	temp = ft_strjoin(*s1, s2);
	free(*s1);
	*s1 = temp;
}

static void	save_line(char **prev, char **line)
{
	char	*ptr_to_n;
	char	*temp;

	ptr_to_n = ft_strchr(*prev, '\n');
	if (ptr_to_n)
	{
		temp = ft_strdup(ptr_to_n + 1);
		*ptr_to_n = '\0';
		*line = ft_strdup(*prev);
		free(*prev);
		*prev = temp;
	}
	else
	{
		*line = *prev;
		*prev = NULL;
	}
}

static int	return_value(char **prev, ssize_t buf_len, char **line)
{
	if (buf_len < 0)
	{
		ft_memdel((void **)prev);
		return (-1);
	}
	if (buf_len == 0 && (*prev == NULL || !ft_strlen(*prev)))
	{	
		ft_memdel((void **)prev);
		return (0);
	}
	save_line(prev, line);
	return (1);
}

int	ft_get_next_line(const int fd, char **line)
{
	static char	*prev[FD_COUNT];
	char		buff[BUFF_SIZE + 1];
	ssize_t		buf_len;

	if (fd < 0 || line == NULL || fd >= FD_COUNT)
		return (-1);
	buf_len = 1;
	while (buf_len > 0 && (!prev[fd] || !ft_strchr(prev[fd], '\n')))
	{
		buf_len = read(fd, buff, BUFF_SIZE);
		buff[buf_len] = '\0';
		if (!prev[fd])
			prev[fd] = ft_strdup(buff);
		else
			join_and_free(&prev[fd], buff);
	}
	return (return_value(&prev[fd], buf_len, line));
}
