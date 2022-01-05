/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:30:08 by ishakuro          #+#    #+#             */
/*   Updated: 2022/01/05 17:16:31 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef FILLIT_H
#define FILLIT_H

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef char **string_array;

typedef struct	s_piece
{
	char	**content;
	int		xlen;
	int		ylen;
	int		xmin;
	int		ymin;
	char	litera;
}				t_piece;

#endif