/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:16:57 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/05 00:07:15 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIGURE_H
# define FIGURE_H

# include "utils/vec3d.h"
# include <libft.h>

//	abstract

typedef enum e_figure_type
{
	f_none,
	f_sphere,
	f_plane,
	f_cylinder,
}					t_figure_type;

typedef struct s_figure
{
	t_figure_type	__type;
	t_vec3d			coordinates;
	t_color			color;
	double			reflectivity;
	t_color			checker;
	void			*bump;
}					t_figure;

int					figure_init(t_figure *self);
typedef void		(*t_figure_del)(t_figure *self);
void				figure_del(t_figure *self);
void				__figure_del(t_figure *self);

#endif
