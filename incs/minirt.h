/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 04:38:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/03 18:01:03 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "objects.h"
# include <libft.h>
# include <mlx.h>

#define USING "\
Usage: ./miniRT <rt-file>\n\
\n\
rt-file format:\n\
\tAmbient\t\tA <ratio> <color>\n\
\tCamera\t\tC <coordinates> <orientation> <fov>\n\
\tLight\t\tL <coordinates> <brightness> <color>\n\
\n\
\tSphere\t\tsp <coordinates> <diameter> <color>\n\
\tPlane\t\tpl <coordinates> <normal> <color>\n\
\tCylinder\tcy <coordinates> <axis> <diameter> <height> <color>\n\
\n\
Made by hshimizu.\n\
github\t: https://github.com/Neko-Sato\n\
profile\t: https://profile.intra.42.fr/users/hshimizu\n\
"

typedef struct s_minirt
{
	t_camera	*camera;
	t_ambient	*ambient;
	t_xlst		*rights;
	t_xlst		*figures;
}				t_minirt;

int				load_rt(t_minirt *rt, char *filename);
void			del_rt(t_minirt *rt);
void			*show_rt(t_minirt *rt, void *mlx, char *title, int size[2]);

int				rt2img(t_minirt *rt, int size[2], unsigned int *img);

#endif
