/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cylinder.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:26:08 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 08:48:36 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef F_CYLINDER_H
# define F_CYLINDER_H

# include "minirt.h"
# include "texture.h"
# include "utils/vec3d.h"
# include <libft.h>

# define IDENTIFIER_F_CYLINDER "cy"

typedef struct s_f_cylinder
{
	t_vec3d				coordinates;
	t_vec3d				axis;
	double				diameter;
	double				height;
	t_texture			texture;
}						t_f_cylinder;

typedef struct s_figure	t_figure;

int						f_cylinder_parser(char *str, t_figure *figure);

#endif
