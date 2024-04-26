/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 04:38:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/04/27 04:47:11 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "object.h"
# include <mlx.h>

typedef struct s_minirt
{
	t_object	*configre;
	t_object	*rights;
	t_object	*figures;
}				t_minirt;

t_minirt		*open_rt(char *filename);

#endif
