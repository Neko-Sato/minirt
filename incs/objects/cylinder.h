/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:26:08 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/08 04:28:26 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "./figure.h"
# include "utils/vec3d.h"

typedef struct s_cylinder
{
	t_figure	__parent;
	t_vec3d		axis;
	float		diameter;
	float		height;
}				t_cylinder;

int				cylinder_init(t_cylinder *self);
void			cylinder_del(t_cylinder *self);

#endif
