/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:01:15 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/13 10:04:06 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AABB_H
# define AABB_H

# include "./vec3d.h"
# include "./ray.h"

typedef struct s_aabb
{
	t_vec3d	min;
	t_vec3d	max;
}			t_aabb;

int			aabb_contains(\
	const t_aabb *aabb, const t_ray *ray, float max_dist);

#endif
