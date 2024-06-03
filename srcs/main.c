/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 05:37:42 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/04 02:24:09 by hshimizu         ###   ########.fr       */
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
		g_class_minirt.put_using();
		return (EXIT_SUCCESS);
	}
	else if (2 < argc)
		ret = TOO_MANY_ARGUMENTS;
	else
	{
		ret = g_class_minirt.load(argv[1], WIDTH_SIZE, HEIGHT_SIZE, &minirt);
		if (!ret)
		{
			minirt.__class->show(&minirt);
			minirt.__class->del(&minirt);
		}
	}
	if (ret)
	{
		rt_perror(ret);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
