/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:42:07 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/11 23:47:15 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# define MAX_DEPTH 5
# define MOVE_UNIT 1
# define ROTATE_UNIT 0.08726646259971647

# include "./camera.h"
# include "./scene.h"
# include "./utils/matrix3x3.h"
# include <libft.h>

typedef struct s_action
{
	int			look_up : 1;
	int			look_down : 1;
	int			look_left : 1;
	int			look_right : 1;
	int			move_forward : 1;
	int			move_backward : 1;
	int			move_left : 1;
	int			move_right : 1;
	int			move_up : 1;
	int			move_down : 1;
}				t_action;

typedef struct s_renderer
{
	void		*mlx;
	void		*win;
	void		*img;
	int			focus;
	int			needs_rendring;
	t_matrix3x3	transform;
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
