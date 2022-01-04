/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishakuro <ishakuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:30:08 by ishakuro          #+#    #+#             */
/*   Updated: 2022/01/03 14:48:58 by ishakuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef FILLIT_H
#define FILLIT_H

typedef struct	s_piece
{
	char	**content;
	int		xlen;
	int		ylen;
	char	litera;
}				t_piece

#endif