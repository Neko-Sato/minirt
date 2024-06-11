/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:16:57 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/11 11:30:51 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIGURE_H
# define FIGURE_H

# include "utils/vec3d.h"
# include <libft.h>

typedef struct s_figure		t_figure;

/*
	Functions here must reference a table to achieve polymorphism.
	When overriding,
	create and replace a new virtual table.
	When adding a new virtual function,
	create and replace a virtual table that is compatible
	with the parent virtual table.
*/
/*
	AABB is an “Axis-Aligned Bounding Box”.
	it's used for rough intersection checks.
	This time, I will not use a tree structure and
	will not make it retain values,
	It may be useful to do a rough intersection check
	when checking intersections.
	Rather than mucking around with trigonometric functions
	every time....
*/

typedef struct s_figure_vtable
{
	void					(*del)(t_figure *self);
}							t_figure_vtable;

typedef struct s_figure
{
	const t_figure_vtable	*_;
	t_vec3d					coordinates;
	t_color					color;
	float					reflectivity;
	t_color					checker;
	void					*bump;
}							t_figure;

int							figure_init(t_figure *self);
void						figure_del(t_figure *self);

#endif
