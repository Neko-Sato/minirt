/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 05:37:42 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/05 00:08:17 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/minirt.h"
#include "rt_errno.h"
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	int			ret;
	t_minirt	minirt;

	if (argc == 1)
	{
		minirt_put_using();
		return (EXIT_SUCCESS);
	}
	else if (2 < argc)
		ret = TOO_MANY_ARGUMENTS;
	else
	{
		ret = minirt_load(argv[1], WIDTH_SIZE, HEIGHT_SIZE, &minirt);
		if (!ret)
		{
			minirt_show(&minirt);
			minirt_del(&minirt);
		}
	}
	if (ret)
	{
		rt_perror(ret);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
