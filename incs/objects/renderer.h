/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:42:07 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/22 00:21:11 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# define PIXELS_PER_SIDE 50000
# define MAX_DEPTH 5
# define MOVE_UNIT 1.0
# define ROTATE_UNIT 0.08726646259971647

# include "./camera.h"
# include "./scene.h"
# include <libft.h>

typedef struct s_action
{
	int			reset : 1;
	int			pitch_up : 1;
	int			pitch_dn : 1;
	int			roll_up : 1;
	int			roll_dn : 1;
	int			yaw_up : 1;
	int			yaw_dn : 1;
	int			forward : 1;
	int			backward : 1;
	int			right : 1;
	int			left : 1;
	int			up : 1;
	int			down : 1;
	int			broaden : 1;
	int			narrow : 1;
}				t_action;

typedef struct s_renderer
{
	void		*mlx;
	void		*win;
	void		*img;
	int			focus;
	int			max_iter;
	int			iter;
	t_camera	save;
	t_action	action;
	t_camera	*camera;
	t_rtobjs	*objs;
}				t_renderer;

typedef struct s_renderer_init
{
	void		*mlx;
	char		*title;
	t_camera	*camera;
	t_rtobjs	*objs;
}				t_renderer_init;

int				renderer_init(t_renderer *self, t_renderer_init *args);
void			renderer_del(t_renderer *self);
void			renderer_set_hook(t_renderer *self);
void			renderer_set_hook2(t_renderer *self);

int				renderer_render(t_renderer *self);
void			renderer_update_transform(t_renderer *self);
int				renderer_loop_hook(t_renderer *self);

#endif
