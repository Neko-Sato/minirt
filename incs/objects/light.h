/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:15:56 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/04 23:08:26 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "utils/vec3d.h"
# include <libft.h>

typedef struct s_light
{
	t_vec3d	coordinates;
	double	brightness;
	t_color	color;
}			t_light;

int			light_init(t_light *self);
void		light_del(t_light *self);

#endif
