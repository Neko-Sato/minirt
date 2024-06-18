/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:21:10 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/18 19:53:11 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H

# include "./figure.h"
# include "utils/vec3d.h"

typedef struct s_triangle
{
	t_figure	__parent;
	t_vec3d		first;
	t_vec3d		second;
	t_vec3d		third;
}				t_triangle;

int				triangle_init(t_triangle *self);
void			triangle_del(t_triangle *self);

void			triangle_update_aabb(t_triangle *self);

#endif
