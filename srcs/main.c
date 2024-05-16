/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:42:22 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 08:50:29 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>

static inline int	internal(char *filename);

int	main(int argc, char *argv[])
{
	int	ret;

	if (argc < 2)
	{
		ft_putstr_fd(USING, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (2 < argc)
		ret = TOO_MANY_ARGUMENTS;
	else
		ret = internal(argv[1]);
	if (ret)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		rt_perror(ret);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static inline int	internal(char *filename)
{
	int					ret;
	t_minirt			rt;

	ret = new_rt(&rt, (int []){WIDTH_SIZE, HEIGHT_SIZE}, filename);
	if (ret)
		return (ret);
	ret = show_rt(&rt);
	del_rt(&rt);
	return (ret);
}
