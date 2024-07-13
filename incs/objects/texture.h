/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:21:20 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/14 00:15:26 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "rt_errno.h"
# include <libft.h>

typedef struct s_texture
{
	t_color	color;
	float	reflectivity;
	t_color	checker;
	void	*bump;
}			t_texture;

typedef struct s_texture_init
{
	t_color	color;
	float	reflectivity;
	t_color	checker;
	void	*bump;
}			t_texture_init;

t_rt_errno	texture_init(\
	t_texture *self, t_texture_init *args);
void		texture_del(\
	t_texture *self);

#endif
