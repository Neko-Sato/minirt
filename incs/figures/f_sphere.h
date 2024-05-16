/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_sphere.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:21:10 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 08:48:43 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef F_SPHERE_H
# define F_SPHERE_H

# include "texture.h"
# include "utils/vec3d.h"
# include <libft.h>

# define IDENTIFIER_F_SPHERE "sp"

typedef struct s_f_sphere
{
	t_vec3d				coordinates;
	double				diameter;
	t_texture			texture;
}						t_f_sphere;

typedef struct s_figure	t_figure;

int						f_sphere_parser(char *str, t_figure *figure);

#endif
