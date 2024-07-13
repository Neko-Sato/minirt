/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:50:51 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/13 17:42:36 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/ambient.h"
#include "utils/ray.h"
#include <libft.h>

t_color	ambient_get_intensity(t_ambient *self, t_scene *scene,
	const t_ray *normal)
{
	t_abstract_light *const	light = (t_abstract_light *)self;

	(void)scene;
	(void)normal;
	return (ft_color_brightness(light->brightness, light->color));
}
