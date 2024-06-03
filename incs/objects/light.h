/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:15:56 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/04 00:23:19 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "utils/vec3d.h"
# include <libft.h>

typedef struct s_light		t_light;

typedef struct s_class_light
{
	int						(*init)(t_light *self);
	void					(*del)(t_light *self);
}							t_class_light;

int							__light_init(t_light *self);
void						__light_del(t_light *self);

extern const t_class_light	g_class_light;

typedef struct s_light
{
	const t_class_light		*__class;
	t_vec3d					coordinates;
	double					brightness;
	t_color					color;
}							t_light;

#endif
