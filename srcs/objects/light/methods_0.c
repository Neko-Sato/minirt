/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:50:51 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/14 13:58:58 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_light.h"
#include "objects/light.h"
#include "objects/scene.h"
#include "utils/vec3d.h"
#include "utils/ray.h"
#include "constants.h"
#include <libft.h>

t_color	light_get_intensity(t_light *self, t_scene *scene, const t_ray *normal)
{
	t_abstract_light *const		light = (t_abstract_light *)self;
	const t_vec3d				v = vec3d_sub(self->coord, normal->c);
	const float					dist = vec3d_abs(v);
	const t_vec3d				o = vec3d_norm(v);
	float						n;

	if ((dist < MIN_DIST || MAX_DIST < dist))
		return ((t_color){.raw = COLOR_RAW_BLACK});
	n = vec3d_dot(o, normal->o);
	if (n < 0 || scene_get_nearest(scene, \
			&(t_ray){o, normal->c}, dist, &(float){0}))
		return ((t_color){.raw = COLOR_RAW_BLACK});
	n = pow(n, GLOSSINESS) * light->brightness;
	return (ft_color_brightness(n, light->color));
}
