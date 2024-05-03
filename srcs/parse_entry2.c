/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_entry2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 07:27:42 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/03 09:58:21 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include <libft.h>

int	parse_ratio(char *str, double *ratio)
{
	double	ratio_tmp;
	char	*endptr;

	ratio_tmp = ft_strtod(str, &endptr);
	if (*endptr || ratio_tmp < 0. || 1. < ratio_tmp)
		return (INCORRECT_FORMAT);
	*ratio = ratio_tmp;
	return (NO_ERROR);
}

int	parse_fov(char *str, int *fov)
{
	int		fov_tmp;
	char	*endptr;

	fov_tmp = ft_strtol(str, &endptr, 10);
	if (*endptr || fov_tmp < 0 || 180 < fov_tmp)
		return (INCORRECT_FORMAT);
	*fov = fov_tmp;
	return (NO_ERROR);
}

int	parse_double(char *str, double *value)
{
	int		tmp;
	char	*endptr;

	tmp = ft_strtod(str, &endptr);
	if (*endptr)
		return (INCORRECT_FORMAT);
	*value = tmp;
	return (NO_ERROR);
}
