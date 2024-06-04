/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 03:30:12 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/05 06:57:26 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "./ambient.h"
# include "./camera.h"
# include "./figure.h"
# include "./light.h"
# include <libft.h>
# include <mlx.h>

typedef struct s_scene
{
	char		title[20];
	t_ambient	*ambient;
	t_camera	*camera;
	t_xlst		*lights;
	t_xlst		*figures;
}				t_scene;

int				scene_init(t_scene *self, char *title);
void			scene_del(t_scene *self);
int				scene_load(t_scene *self, char *filename);
int				scene_set_ambient(t_scene *self, t_ambient *ambient);
int				scene_set_camera(t_scene *self, t_camera *camera);
int				scene_add_light(t_scene *self, t_light *light);
int				scene_add_figure(t_scene *self, t_figure *figure);

#endif
