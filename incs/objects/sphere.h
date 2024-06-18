/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:21:10 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/18 18:53:42 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "./figure.h"

typedef struct s_sphere
{
	t_figure	__parent;
	t_vec3d		coordinates;
	float		diameter;
}				t_sphere;

int				sphere_init(t_sphere *self);
void			sphere_del(t_sphere *self);

void			sphere_update_aabb(t_sphere *self);

#endif
