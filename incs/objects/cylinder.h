/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:26:08 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/03 06:35:57 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "./figure.h"
# include "utils/vec3d.h"

typedef struct s_cylinder		t_cylinder;

typedef struct s_class_cylinder
{
	int							(*init)(t_cylinder *self);
	void						(*del)(t_cylinder *self);
}								t_class_cylinder;

int								__cylinder_init(t_cylinder *self);
void							__cylinder_del(t_cylinder *self);

extern const t_class_cylinder	g_class_cylinder;

typedef struct s_cylinder
{
	const t_class_cylinder		*__class;
	t_figure					__parent;
	t_vec3d						axis;
	double						diameter;
	double						height;
}								t_cylinder;

#endif
