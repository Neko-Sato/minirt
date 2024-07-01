/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:26:08 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/29 01:16:48 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUARE_H
# define SQUARE_H

# include "./figure.h"
# include "utils/vec3d.h"
# include <libft.h>

typedef struct s_square
{
	t_figure		__parent;
	t_vec3d			coord;
	t_vec3d			orient;
	float			size;
}					t_square;

typedef struct s_square_init
{
	t_vec3d			coord;
	t_vec3d			orient;
	float			size;
	t_color			color;
	t_figure_opt	opt;
}					t_square_init;

t_rt_errno			square_init(t_square *self, t_square_init *args);
void				square_del(t_square *self);

void				square_set_aabb(t_square *self);
int					square_intersect(t_square *self, const t_ray *r,
						float max_dist, float *t);

#endif
