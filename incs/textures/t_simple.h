/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_simple.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 02:14:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/15 22:47:58 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SIMPLE_H
# define T_SIMPLE_H

# include <libft.h>

# define IDENTIFIER_T_SIMPLE "simple"

typedef struct s_t_simple
{
	t_color					color;
}							t_t_simple;

typedef struct s_texture	t_texture;

int							t_simple_parser(char *str, t_texture *texture);

#endif
