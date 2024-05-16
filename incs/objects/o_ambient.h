/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_ambient.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:13:17 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/15 22:18:42 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef O_AMBIENT_H
# define O_AMBIENT_H

# include <libft.h>

# define IDENTIFIER_O_AMBIENT "A"

typedef struct s_o_ambient
{
	double				ratio;
	t_color				color;
}						t_o_ambient;

typedef struct s_object	t_object;

int						o_ambient_parser(char *str, t_object *object);

#endif
