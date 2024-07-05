/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 03:30:12 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/05 18:06:25 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "./ambient.h"
# include "./camera.h"
# include "./figure.h"
# include "./light.h"
# include "rt_errno.h"
# include <libft.h>

typedef struct s_scene
{
	char	*title;
	t_xlst	*cameras;
	t_xlst	*ambients;
	t_xlst	*lights;
	t_xlst	*figures;
}			t_scene;

typedef struct s_scene_init
{
	char	*title;
}			t_scene_init;

t_rt_errno	scene_init(t_scene *self, t_scene_init *args);
void		scene_del(t_scene *self);

t_rt_errno	scene_load(t_scene *self, char *filename);

t_rt_errno	scene_add_ambient(t_scene *self, t_ambient *ambient);
t_rt_errno	scene_add_camera(t_scene *self, t_camera *camera);
t_rt_errno	scene_add_light(t_scene *self, t_light *light);
t_rt_errno	scene_add_figure(t_scene *self, t_figure *figure);

t_color		scene_trace(t_scene *self, const t_ray *r, float max_dist,
				int max_depth);
t_color		scene_rough_trace(t_scene *self, const t_ray *r, float max_dist);

t_figure	*scene_get_nearest(t_scene *self, const t_ray *r, float max_dist,
				float *dist);
void		scene_apply_ambients(t_scene *self, t_color *color);
void		scene_apply_lights(t_scene *self, const t_ray *normal,
				t_color *color);

#endif
