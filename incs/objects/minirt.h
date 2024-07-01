/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 01:51:22 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/30 23:06:13 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "./scene.h"
# include <libft.h>

# define USING "\
Usage: ./miniRT <rt-file>\n\
\n\
rt-file format:\n\
\tAmbient\t\tA <ratio> <color>\n\
\tCamera\t\tC <coordinates> <orientation> <fov>\n\
\tLight\t\tL <coordinates> <brightness> <color>\n\
\n\
\tSphere\t\tsp <coordinates> <diameter> <color>\n\
\tPlane\t\tpl <coordinates> <orientation> <color>\n\
\tCylinder\tcy <coordinates> <axis> <diameter> <height> <color>\n\
\tTriangle\ttr <first> <second> <third> <color>\n\
\tSqaure\t\tsq <coordinates> <orientation> <size> <color>\n\
\n\
key operation:\n\
\tUp\tMove forward.\n\
\tDown\tMove backward.\n\
\tLeft\tMove left.\n\
\tRight\tMove right.\n\
\tz\tMove down.\n\
\tc\tMove up.\n\
\te\tRoll up.\n\
\tq\tRoll down.\n\
\tw\tPitch up.\n\
\ts\tPitch down.\n\
\ta\tYaw up.\n\
\td\tYaw down.\n\
\tk\tIncrease fov.\n\
\tj\tDecrease fov.\n\
\tr\tReturn to initial position.\n\
\tEsc\tClose window.\n\
\n\
Made by hshimizu.\n\
github\t: https://github.com/Neko-Sato\n\
profile\t: https://profile.intra.42.fr/users/hshimizu\n\
"

# ifndef ALLOW_MULTIPLE_CAMERAS
#  define ALLOW_MULTIPLE_CAMERAS 0
# endif

# ifndef ALLOW_MULTIPLE_AMIBIENTS
#  define ALLOW_MULTIPLE_AMIBIENTS 0
# endif

# ifndef ALLOW_FOV_UNLIMITED
#  define ALLOW_FOV_UNLIMITED 0
# endif

# ifndef ALTERNATIVE_UP_VECTOR
#  define ALTERNATIVE_UP_VECTOR 1
# endif

typedef struct s_minirt
{
	void		*mlx;
	t_rt_errno	errno;
	t_xlst		*scenes;
	t_xlst		*renderers;
}				t_minirt;

typedef struct s_minirt_init
{
}				t_minirt_init;

t_rt_errno		minirt_init(t_minirt *self, t_minirt_init *args);
void			minirt_del(t_minirt *self);

void			minirt_set_hook(t_minirt *self);
t_rt_errno		minirt_loop(t_minirt *self);
t_rt_errno		minirt_add_scene(t_minirt *self, t_scene *scene);

void			minirt_put_using(void);

#endif
