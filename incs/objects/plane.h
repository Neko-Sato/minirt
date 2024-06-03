/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:26:08 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/03 06:35:38 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "./figure.h"
# include "utils/vec3d.h"

typedef struct s_plane		t_plane;

typedef struct s_class_plane
{
	int						(*init)(t_plane *self);
	void					(*del)(t_plane *self);
}							t_class_plane;

int							__plane_init(t_plane *self);
void						__plane_del(t_plane *self);

extern const t_class_plane	g_class_plane;

typedef struct s_plane
{
	const t_class_plane		*__class;
	t_figure				__parent;
	t_vec3d					normal;
}							t_plane;

#endif
