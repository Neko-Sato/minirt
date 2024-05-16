/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 02:02:30 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/15 14:30:28 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "object.h"
# include <libft.h>

typedef struct s_scene
{
	char		*title;
	t_o_camera	*camera;
	t_o_ambient	*ambient;
	t_xlst		*rights;
	t_xlst		*figures;
}				t_scene;

int				load_rt(t_scene *scene, char *filename);
void			scene_del(t_scene *scene);

int				rt2img(t_scene *scene, unsigned int *img, int size[2]);

#endif
