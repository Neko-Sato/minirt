/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 03:57:27 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 08:53:28 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minirt.h"
# include "utils/vec3d.h"
# include <libft.h>
# include <stddef.h>

typedef int			(*t_parser_fun)(char *str, void *value);

typedef struct s_parser_entry
{
	size_t			dest_offset;
	t_parser_fun	fun;
}					t_parser_entry;

int					parser(char *str, const t_parser_entry entries[],
						size_t size, void *value);

int					parse_int(char *str, int *value);
int					parse_dobule(char *str, double *value);
int					parse_vec3d(char *str, t_vec3d *value);
int					parse_color(char *str, t_color *value);

int					parse_norm_vec3d(char *str, t_vec3d *value);
int					parse_rate(char *str, double *value);

#endif
