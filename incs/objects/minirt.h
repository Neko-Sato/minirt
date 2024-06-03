/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 03:12:12 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/04 02:24:07 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "./scene.h"
# include <libft.h>

# define USING \
	"\
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

# ifndef WIDTH_SIZE
#  define WIDTH_SIZE 1000
# endif
# ifndef HEIGHT_SIZE
#  define HEIGHT_SIZE 800
# endif

typedef struct s_minirt		t_minirt;

typedef struct s_class_minirt
{
	int						(*init)(t_minirt *self, t_scene *scene, int width,
			int height);
	void					(*del)(t_minirt *self);
	void					(*put_using)(void);
	void					(*show)(t_minirt *self);
	int						(*load)(char *filename, int width, int height,
			t_minirt *minirt);
	void					(*render)(t_minirt *self);
}							t_class_minirt;

int							__minirt_init(t_minirt *self, t_scene *scene,
								int width, int height);
void						__minirt_del(t_minirt *self);
void						__minirt_put_using(void);
void						__minirt_show(t_minirt *self);
int							__minirt_load(char *filename, int width, int height,
								t_minirt *minirt);
void						__minirt_render(t_minirt *self);

extern const t_class_minirt	g_class_minirt;

typedef struct s_minirt
{
	const t_class_minirt	*__class;
	void					*mlx;
	void					*win;
	void					*img;
	int						width;
	int						height;
	int						needs_rendering;
	t_scene					*scene;
}							t_minirt;

#endif
