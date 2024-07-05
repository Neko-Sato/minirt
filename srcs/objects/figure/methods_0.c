/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:21:11 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/05 18:10:01 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/figure.h"
#include "rt_errno.h"
#include <math.h>
#include <libft.h>
#include <stdlib.h>

int	figure_intersect(t_figure *self, const t_ray *r, float max_dist, float *t)
{
	float	dist[2];
	float	tmp[2];
	int		i;

	ft_memcpy(dist, (float []){0, max_dist}, sizeof(dist));
	i = 0;
	while (i < 3)
	{
		if (r->o._[i])
		{
			tmp[0] = (self->aabb[0]._[i] - r->c._[i]) / r->o._[i];
			tmp[1] = (self->aabb[1]._[i] - r->c._[i]) / r->o._[i];
			dist[0] = fmax(dist[0], fmin(tmp[0], tmp[1]));
			dist[1] = fmin(dist[1], fmax(tmp[0], tmp[1]));
			if (dist[0] > dist[1])
				return (0);
		}
		else if (r->c._[i] < self->aabb[0]._[i]
			|| r->c._[i] > self->aabb[1]._[i])
			return (0);
		i++;
	}
	*t = dist[0];
	return (1);
}

t_color	figure_get_color(t_figure *self, const t_ray *normal)
{
	(void)normal;
	return (self->color);
}
