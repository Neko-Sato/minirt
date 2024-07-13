/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 01:51:22 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/12 21:02:04 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "./scene.h"
# include <libft.h>

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

t_rt_errno		minirt_init(\
	t_minirt *self, t_minirt_init *args);
void			minirt_del(\
	t_minirt *self);

void			minirt_set_hook(\
	t_minirt *self);
t_rt_errno		minirt_loop(\
	t_minirt *self);
t_rt_errno		minirt_add_scene(\
	t_minirt *self, t_scene *scene);

void			minirt_put_using(void);

#endif
