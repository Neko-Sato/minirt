/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:50:51 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/24 05:36:35 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_light.h"
#include "objects/light.h"
#include "objects/scene.h"
#include "utils/vec3.h"
#include "utils/ray.h"
#include "constants.h"
#include <libft.h>

t_color	light_get_intensity(t_light *self, t_scene *scene, const t_ray *normal)
{
	t_abstract_light *const		light = (t_abstract_light *)self;
	const t_vec3				v = vec3_sub(self->coord, normal->c);
	const float					dist = vec3_abs(v);
	const t_vec3				o = vec3_norm(v);
	float						n;

	if ((dist < MIN_DIST || MAX_DIST < dist))
		return ((t_color){.raw = COLOR_RAW_BLACK});
	n = vec3_dot(o, normal->o);
	if (n < MIN_DIST || scene_get_nearest(scene, \
			&(t_ray){o, normal->c}, dist, &(float){0}))
		return ((t_color){.raw = COLOR_RAW_BLACK});
	return (ft_color_brightness(n * light->brightness, light->color));
}
