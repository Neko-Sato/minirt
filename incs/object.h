/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 01:59:16 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/15 22:04:30 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "./objects/o_ambient.h"
# include "./objects/o_camera.h"
# include "./objects/o_figure.h"
# include "./objects/o_light.h"

typedef enum e_object_type
{
	o_none = -1,
	o_ambient,
	o_camera,
	o_light,
	o_figure,
}					t_object_type;

typedef union u_object_value
{
	t_o_ambient		ambient;
	t_o_camera		camera;
	t_o_light		light;
	t_o_figure		figure;
}					t_object_value;

typedef struct s_object
{
	t_object_type	type;
	t_object_value	value;
}					t_object;

int					object_parser(char *str, t_object *object);
int					object_parser_internal(char *identifier, char *str,
						t_object *object);

#endif
