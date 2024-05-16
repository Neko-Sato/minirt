/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:16:57 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 09:30:16 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIGURE_H
# define FIGURE_H

# include "./figures/f_cylinder.h"
# include "./figures/f_plane.h"
# include "./figures/f_sphere.h"

typedef enum e_figure_type
{
	f_none = -1,
	f_sphere,
	f_plane,
	f_cylinder,
}					t_figure_type;

typedef union u_figure_value
{
	t_f_sphere		sphere;
	t_f_plane		plane;
	t_f_cylinder	cylinder;
}					t_figure_value;

typedef struct s_figure
{
	t_figure_type	type;
	t_figure_value	value;
}					t_figure;

int					figure_parser(char *str, t_figure *figure);
int					figure_parser_internal(char *identifier, char *str,
						t_figure *figure);

#endif
