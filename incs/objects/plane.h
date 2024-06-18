/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:21:10 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/18 20:24:36 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "./figure.h"
# include "utils/vec3d.h"

typedef struct s_plane
{
	t_figure	__parent;
	t_vec3d		coordinates;
	t_vec3d		orientation;
}				t_plane;

int				plane_init(t_plane *self);
void			plane_del(t_plane *self);

void			plane_update_aabb(t_plane *self);

#endif
