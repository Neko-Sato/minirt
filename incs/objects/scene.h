/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 03:30:12 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/24 03:28:30 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "./abstract_figure.h"
# include "./abstract_light.h"
# include "./camera.h"
# include "rt_errno.h"
# include <libft.h>

typedef struct s_scene
{
	char				*title;
	size_t				cameras_size;
	t_camera			**cameras;
	size_t				lights_size;
	t_abstract_light	**lights;
	size_t				figures_size;
	t_abstract_figure	**figures;
}						t_scene;

typedef struct s_scene_init
{
	char				*title;
	size_t				cameras_size;
	t_camera			**cameras;
	size_t				lights_size;
	t_abstract_light	**lights;
	size_t				figures_size;
	t_abstract_figure	**figures;
}						t_scene_init;

t_rt_errno				scene_init(\
	t_scene *self, t_scene_init *args);
void					scene_del(\
	t_scene *self);

t_abstract_figure		*scene_get_nearest(\
	t_scene *self, const t_ray *ray, float max_dist, float *dist);
t_color					scene_get_intensity(\
	t_scene *self, const t_ray *normal);
t_color					scene_trace(\
	t_scene *self, const t_ray *ray, int max_depth);

t_rt_errno				scene_load(\
	t_scene *scene, char *filename);

#endif
