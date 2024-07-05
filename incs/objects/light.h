/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:15:56 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/05 08:37:14 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "rt_errno.h"
# include "utils/vec3d.h"
# include <libft.h>

typedef struct s_light
{
	t_vec3d	coord;
	t_color	color;
}			t_light;

typedef struct s_light_init
{
	t_vec3d	coord;
	float	brightness;
	t_color	color;
}			t_light_init;

t_rt_errno	light_init(t_light *self, t_light_init *args);
void		light_del(t_light *self);

#endif
