/* ************************************************************************** */
/*\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t*/
/*\t\t\t\t\t\t\t\t\t\t\t\t\t\t:::\t  ::::::::*/
/*minirt.h\t\t\t\t\t\t\t\t\t\t:+:\t  :+:\t:+:*/
/*\t\t\t\t\t\t\t\t\t\t\t\t\t+:+ +:+\t\t +:+\t */
/*By: hshimizu <hshimizu@student.42.fr>\t\t  +#+  +:+\t+#+\t\t*/
/*\t\t\t\t\t\t\t\t\t\t\t\t+#+#+#+#+#++#+\t\t*/
/*Created: 2024/06/02 03:12:12 by hshimizu\t\t  #+#\t#+#\t\t\t */
/*Updated: 2024/06/21 23:43:40 by hshimizu\t\t ###########.fr\t*/
/*\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t*/
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/*
	My minirt is moving, asshole!
	That's why a few are all floats!
	You got a problem with that?
*/

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

typedef struct s_minirt
{
	void	*mlx;
	int		errno;
	t_xlst	*scenes;
	t_xlst	*renderers;
}			t_minirt;

int			minirt_init(t_minirt *self);
void		minirt_del(t_minirt *self);
void		minirt_put_using(void);
int			minirt_loop_hook(t_minirt *self);
int			minirt_loop(t_minirt *self);
int			minirt_add_scene(t_minirt *self, t_scene *scene);

#endif
