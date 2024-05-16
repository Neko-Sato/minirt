/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_light.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:15:56 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/15 22:19:22 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef O_LIGHT_H
# define O_LIGHT_H

# include "utils/vec3d.h"
# include <libft.h>

# define IDENTIFIER_O_LIGHT "L"

typedef struct s_o_light
{
	t_vec3d				coordinates;
	double				brightness;
	t_color				color;
}						t_o_light;

typedef struct s_object	t_object;

int						o_light_parser(char *str, t_object *object);

#endif
