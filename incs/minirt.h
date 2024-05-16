/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 04:38:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 08:51:14 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "object.h"
# include "parser.h"
# include "texture.h"
# include "rt_errno.h"
# include "scene.h"
# include <mlx.h>

# define USING "\
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

# define RT_DELIMIITER " \t\n"

# ifndef WIDTH_SIZE
#  define WIDTH_SIZE 1000
# endif
# ifndef HEIGHT_SIZE
#  define HEIGHT_SIZE 800
# endif

typedef struct s_minirt
{
	void	*mlx;
	void	*win;
	void	*img;
	int		size[2];
	int		needs_rendering;
	t_scene	scene;
}			t_minirt;

int			new_rt(t_minirt *rt, int size[2], char *filename);
void		del_rt(t_minirt *rt);

int			show_rt(t_minirt *rt);

#endif
