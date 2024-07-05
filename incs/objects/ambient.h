/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:13:17 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/05 08:36:59 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMBIENT_H
# define AMBIENT_H

# include "rt_errno.h"
# include <libft.h>

typedef struct s_ambient
{
	t_color	color;
}			t_ambient;

typedef struct s_ambient_init
{
	float	ratio;
	t_color	color;
}			t_ambient_init;

t_rt_errno	ambient_init(t_ambient *self, t_ambient_init *args);
void		ambient_del(t_ambient *self);

#endif
