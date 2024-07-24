/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:01:15 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/24 23:50:34 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AABB_H
# define AABB_H

# include "./mat3x3.h"
# include "./ray.h"
# include "./vec3.h"

typedef struct s_aabb
{
	t_vec3	min;
	t_vec3	max;
}			t_aabb;

int			aabb_contains(const t_aabb *aabb, const t_ray *ray, float max_dist);
void		aabb_expand(t_aabb *aabb, const t_vec3 *point);
t_aabb		aabb_merge(const t_aabb *a, const t_aabb *b);
t_aabb		aabb_transform(const t_aabb *aabb, const t_mat3x3 *rotation,
				const t_vec3 *position);
float		aabb_surface_area(const t_aabb *aabb);

#endif
