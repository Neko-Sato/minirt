/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:16:57 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/07 16:24:04 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIGURE_H
# define FIGURE_H

# include "utils/vec3d.h"
# include <libft.h>

typedef struct s_figure t_figure;

typedef struct s_figure_vtable
{
	void					(*del)(t_figure *self);
}							t_figure_vtable;

typedef struct s_figure
{
	const t_figure_vtable	*__vtable;
	t_vec3d					coordinates;
	t_color					color;
	double					reflectivity;
	t_color					checker;
	void					*bump;
}							t_figure;

int							figure_init(t_figure *self);
void						figure_del(t_figure *self);

#endif
