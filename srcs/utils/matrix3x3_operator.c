/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3x3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 04:43:45 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/08 04:24:43 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/matrix3x3.h"
#include "utils/vec3d.h"

t_matrix3x3	matrix3x3_add(t_matrix3x3 a, t_matrix3x3 b)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			a._[i][j] += b._[i][j];
			j++;
		}
		i++;
	}
	return (a);
}

t_matrix3x3	matrix3x3_sub(t_matrix3x3 a, t_matrix3x3 b)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			a._[i][j] -= b._[i][j];
			j++;
		}
		i++;
	}
	return (a);
}

t_matrix3x3	matrix3x3_mul(t_matrix3x3 a, t_matrix3x3 b)
{
	t_matrix3x3	c;
	int			i;
	int			j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			c._[i][j] = a._[i][0] * b._[0][j] + a._[i][1] * b._[1][j]
				+ a._[i][2] * b._[2][j];
			j++;
		}
		i++;
	}
	return (c);
}

t_matrix3x3	matrix3x3_mul_scalar(float n, t_matrix3x3 a)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			a._[i][j] *= n;
			j++;
		}
		i++;
	}
	return (a);
}

t_vec3d	matrix3x3_mul_vec3d(t_matrix3x3 a, t_vec3d b)
{
	t_vec3d	c;
	int		i;

	i = 0;
	while (i < 3)
	{
		c._[i] = vec3d_dot((t_vec3d){{a._[i][0], a._[i][1], a._[i][2]}}, b);
		i++;
	}
	return (c);
}
