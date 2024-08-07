/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:50:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/13 13:18:00 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_light.h"
#include "objects/light.h"
#include "rt_errno.h"

static const t_abstract_light_vtable	g_vtable = {
	.del = abstract_light_del,
	.get_intensity = (void *)light_get_intensity,
};

t_rt_errno	light_init(t_light *self, t_light_init *args)
{
	t_rt_errno	ret;

	*self = (t_light){};
	ret = abstract_light_init((t_abstract_light *)self,
			&(t_abstract_light_init){
			.color = args->color,
			.brightness = args->brightness,
		});
	if (ret)
		return (ret);
	self->coord = args->coord;
	((t_abstract_light *)self)->_ = &g_vtable;
	return (SUCCESS);
}
