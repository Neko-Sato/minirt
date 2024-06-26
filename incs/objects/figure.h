/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:16:57 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/01 23:59:10 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIGURE_H
# define FIGURE_H

# include "rt_errno.h"
# include "utils/ray.h"
# include "utils/vec3d.h"
# include <libft.h>

typedef struct s_figure_vtable	t_figure_vtable;

typedef struct s_figure
{
	const t_figure_vtable		*_;
	t_color						color;
	float						reflectivity;
	t_color						checker;
	void						*bump;
	t_vec3d						aabb[2];
}								t_figure;

typedef struct s_figure_vtable
{
	void						(*del)(t_figure *self);
	int							(*intersect)(t_figure *self, const t_ray *r,
			float max_dist, float *t);
	union u_color				(*get_color)(t_figure *self, const t_vec3d *p);
}								t_figure_vtable;

typedef struct s_figure_opt
{
	float						reflectivity;
	t_color						checker;
	void						*bump;
}								t_figure_opt;

typedef struct s_figure_init
{
	t_color						color;
	t_figure_opt				opt;
}								t_figure_init;

t_rt_errno						figure_init(t_figure *self,
									t_figure_init *args);
void							figure_del(t_figure *self);

int								figure_intersect(t_figure *self, const t_ray *r,
									float max_dist, float *t);
t_color							figure_get_color(t_figure *self,
									const t_vec3d *p);

#endif
