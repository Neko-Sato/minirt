/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 01:44:25 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/15 22:43:38 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "./textures/t_simple.h"
# include <libft.h>

typedef enum e_texture_type
{
	t_none = -1,
	t_simple,
}					t_texture_type;

typedef union e_texture_value
{
	t_t_simple		simple;
}					t_texture_value;

typedef struct s_texture
{
	t_texture_type	type;
	t_texture_value	value;
}					t_texture;

int					texture_parser(char *str, t_texture *texture);
int					texture_parser_internal(char *identifier, char *str,
						t_texture *texture);

#endif