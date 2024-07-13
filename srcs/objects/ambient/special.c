/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:50:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/13 13:17:40 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/ambient.h"
#include "objects/abstract_light.h"
#include "rt_errno.h"

static const t_abstract_light_vtable	g_vtable = {
	.del = abstract_light_del,
	.get_intensity = (void *)ambient_get_intensity,
};

t_rt_errno	ambient_init(t_ambient *self, t_ambient_init *args)
{
	t_rt_errno	ret;

	*self = (t_ambient){};
	ret = abstract_light_init((t_abstract_light *)self,
			&(t_abstract_light_init){
			.color = args->color,
			.brightness = args->brightness,
		});
	if (ret)
		return (ret);
	((t_abstract_light *)self)->_ = &g_vtable;
	return (SUCCESS);
}
