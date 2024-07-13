/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:13:17 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/13 13:18:39 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "./abstract_light.h"
# include "utils/ray.h"
# include "utils/vec3d.h"
# include "rt_errno.h"
# include <libft.h>

typedef struct s_light
{
	t_abstract_light	__parent;
	t_vec3d				coord;
}						t_light;

typedef struct s_light_init
{
	t_vec3d				coord;
	t_color				color;
	float				brightness;
}						t_light_init;

t_rt_errno				light_init(\
	t_light *self, t_light_init *args);

t_color					light_get_intensity(\
	t_light *self, t_scene *scene, const t_ray *normal);

#endif
