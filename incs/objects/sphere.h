/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:21:10 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/03 06:35:25 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "./figure.h"

typedef struct s_sphere		t_sphere;

typedef struct s_class_sphere
{
	int						(*init)(t_sphere *self);
	void					(*del)(t_sphere *self);
}							t_class_sphere;

int							__sphere_init(t_sphere *self);
void						__sphere_del(t_sphere *self);

extern const t_class_sphere	g_class_sphere;

typedef struct s_sphere
{
	const t_class_sphere	*__class;
	t_figure				__parent;
	double					diameter;
}							t_sphere;

#endif
