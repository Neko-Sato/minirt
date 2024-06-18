/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:26:08 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/18 19:49:27 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUARE_H
# define SQUARE_H

# include "./figure.h"
# include "utils/vec3d.h"

typedef struct s_square
{
	t_figure	__parent;
	t_vec3d		coordinates;
	t_vec3d		orientation;
	float		size;
}				t_square;

int				square_init(t_square *self);
void			square_del(t_square *self);

void			square_update_aabb(t_square *self);

#endif
