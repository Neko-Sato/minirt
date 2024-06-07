/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:16:57 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/08 05:16:23 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIGURE_H
# define FIGURE_H

# include "utils/ray.h"
# include "utils/vec3d.h"
# include <libft.h>

typedef struct s_figure		t_figure;

/*
	Functions here must reference a table to achieve polymorphism.
	When overriding,
	create and replace a new virtual table.
	When adding a new virtual function,
	create and replace a virtual table that is compatible
	with the parent virtual table.
*/
typedef struct s_figure_vtable
{
	void					(*del)(t_figure *self);
	int						(*intersect)(t_figure *self, t_ray *ray,
			t_vec3d *result);
	int						(*normal_vector)(t_figure *self,
			t_vec3d *coordinates, t_vec3d *result);
}							t_figure_vtable;

typedef struct s_figure
{
	const t_figure_vtable	*_;
	t_vec3d					coordinates;
	t_color					color;
	float					reflectivity;
	t_color					checker;
	void					*bump;
}							t_figure;

int							figure_init(t_figure *self);
void						figure_del(t_figure *self);

/*
int	figure_intersect(t_figure *self, t_ray *ray, t_vec3d *result)
{
	The intersection of a vector and a vector is obtained.
	If they do not intersect, the return value is 0.
	You will use it to find distances and normal vectors.
}

int	figure_normal_vector(t_figure *self, t_vec3d *coordinates, t_vec3d *result)
{
	Calculate the normal vector to the coordinates.
	If something goes wrong, return -1.
	But will not happen.
}
*/

#endif
