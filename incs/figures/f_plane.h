/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_plane.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:26:08 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 08:48:39 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef F_PLANE_H
# define F_PLANE_H

# include "texture.h"
# include "utils/vec3d.h"
# include <libft.h>

# define IDENTIFIER_F_PLANE "pl"

typedef struct s_f_plane
{
	t_vec3d				coordinates;
	t_vec3d				normal;
	t_texture			texture;
}						t_f_plane;

typedef struct s_figure	t_figure;

int						f_plane_parser(char *str, t_figure *figure);

#endif
