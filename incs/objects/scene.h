/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 03:30:12 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/04 01:54:05 by hshimizu         ###   ########.fr       */
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

typedef struct s_scene		t_scene;

typedef struct s_class_scene
{
	int						(*init)(t_scene *self, char *filename);
	void					(*del)(t_scene *self);
	int						(*load)(t_scene *self, char *filename);
	void					(*drawing)(t_scene *scene, unsigned int *data,
			int width, int height);
	int						(*set_ambient)(t_scene *self, t_ambient *ambient);
	int						(*set_camera)(t_scene *self, t_camera *camera);
	int						(*add_light)(t_scene *self, t_light *light);
	int						(*add_figure)(t_scene *self, t_figure *figure);
}							t_class_scene;

int							__scene_init(t_scene *self, char *filename);
void						__scene_del(t_scene *self);
int							__scene_load(t_scene *self, char *filename);
void						__scene_drawing(t_scene *scene, unsigned int *data,
								int width, int height);
int							__scene_set_ambient(t_scene *self,
								t_ambient *ambient);
int							__scene_set_camera(t_scene *self, t_camera *camera);
int							__scene_add_light(t_scene *self, t_light *light);
int							__scene_add_figure(t_scene *self, t_figure *figure);

extern const t_class_scene	g_class_scene;

typedef struct s_scene
{
	const t_class_scene		*__class;
	char					title[20];
	t_ambient				*ambient;
	t_camera				*camera;
	t_xlst					*lights;
	t_xlst					*figures;
}							t_scene;

#endif
