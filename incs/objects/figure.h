/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:16:57 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/03 06:31:01 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIGURE_H
# define FIGURE_H

# include "utils/vec3d.h"
# include <libft.h>

typedef struct s_figure		t_figure;

typedef struct s_class_figure
{
	int						(*init)(t_figure *self);
	void					(*del)(t_figure *self);
}							t_class_figure;

int							__figure_init(t_figure *self);
void						__figure_del(t_figure *self);

extern const t_class_figure	g_class_figure;

typedef struct s_figure
{
	const t_class_figure	*__class;
	t_vec3d					coordinates;
	t_color					color;
	double					reflectivity;
	t_color					checker;
	void					*bump;
}							t_figure;

#endif
