/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 03:12:12 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/08 04:30:12 by hshimizu         ###   ########.fr       */
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
\tPlane\t\tpl <coordinates> <normal> <color>\n\
\tCylinder\tcy <coordinates> <axis> <diameter> <height> <color>\n\
\n\
Made by hshimizu.\n\
github\t: https://github.com/Neko-Sato\n\
profile\t: https://profile.intra.42.fr/users/hshimizu\n\
"

# define ITER_MAX 5
# define MOVE_UNIT 1
# define ROTATE_UNIT 0.03490658503988659

typedef struct s_minirt
{
	void	*mlx;
	int		errno;
	t_scene	*scene;
	int		needs_rendering;
	void	*win;
	void	*img;
}			t_minirt;

int			minirt_init(t_minirt *self, t_scene *scene);
void		minirt_del(t_minirt *self);
void		minirt_put_using(void);
int			minirt_show(t_minirt *self);
int			minirt_render(t_minirt *self);

#endif
