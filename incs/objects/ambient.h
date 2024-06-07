/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:13:17 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/08 04:28:15 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMBIENT_H
# define AMBIENT_H

# include <libft.h>

typedef struct s_ambient
{
	float	ratio;
	t_color	color;
}			t_ambient;

int			ambient_init(t_ambient *self);
void		ambient_del(t_ambient *self);

#endif
