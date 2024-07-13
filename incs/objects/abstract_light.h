/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_light.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:46:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/14 03:16:38 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_LIGHT_H
# define ABSTRACT_LIGHT_H

# include "utils/ray.h"
# include "rt_errno.h"
# include <libft.h>

typedef struct s_abstract_light_vtable	t_abstract_light_vtable;

typedef struct s_abstract_light
{
	const t_abstract_light_vtable		*_;
	t_color								color;
	float								brightness;
}										t_abstract_light;

typedef struct s_scene					t_scene;

typedef void							(*t_abstract_light_del_fn)(
	t_abstract_light *self);
typedef t_color							(*t_abstract_light_get_intensity_fn)(
	t_abstract_light *self, t_scene *scene, const t_ray *normal);

typedef struct s_abstract_light_vtable
{
	t_abstract_light_del_fn				del;
	t_abstract_light_get_intensity_fn	get_intensity;
}										t_abstract_light_vtable;

typedef struct s_abstract_light_init
{
	t_color								color;
	float								brightness;
}										t_abstract_light_init;

t_rt_errno								abstract_light_init(\
	t_abstract_light *self, t_abstract_light_init *args);
void									abstract_light_del(\
	t_abstract_light *self);

#endif
