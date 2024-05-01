/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 04:38:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/02 04:22:02 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "objects.h"
# include <libft.h>

typedef struct s_minirt
{
	t_camera	*camera;
	t_ambient	*ambient;
	t_xlst		*rights;
	t_xlst		*figures;
}				t_minirt;

int				load_rt(t_minirt *rt, char *filename);
void			del_rt(t_minirt *rt);

#endif
