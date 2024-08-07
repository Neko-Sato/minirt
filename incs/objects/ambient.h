/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:13:17 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/13 13:18:30 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMBIENT_H
# define AMBIENT_H

# include "./abstract_light.h"
# include "utils/ray.h"
# include "rt_errno.h"
# include <libft.h>

typedef struct s_ambient
{
	t_abstract_light	__parent;
}						t_ambient;

typedef struct s_ambient_init
{
	t_color	color;
	float	brightness;
}			t_ambient_init;

t_rt_errno	ambient_init(\
	t_ambient *self, t_ambient_init *args);

t_color		ambient_get_intensity(\
	t_ambient *self, t_scene *scene, const t_ray *normal);

#endif
