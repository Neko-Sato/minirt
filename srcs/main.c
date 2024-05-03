/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:42:22 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/03 13:01:14 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "rt_error.h"
#include <stdlib.h>
#include <unistd.h>

void	put_using(void);

int	main(int argc, char *argv[])
{
	int			ret;
	t_minirt	rt;

	if (argc < 2)
	{
		put_using();
		return (EXIT_FAILURE);
	}
	else if (2 < argc)
		ret = TOO_MANY_ARGUMENTS;
	else
		ret = load_rt(&rt, argv[1]);
	if (!ret)
		ret = NO_ERROR;
	if (ret)
	{
		put_rt_err(ret);
		return (EXIT_FAILURE);
	}
	del_rt(&rt);
	return (EXIT_SUCCESS);
}

void	put_using(void)
{
	ft_putstr_fd("Usage: ./miniRT <rt-file>\n", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd("rt-file format:\n", STDERR_FILENO);
	ft_putstr_fd("\tAmbient\t\tA <ratio> <color>\n", STDERR_FILENO);
	ft_putstr_fd("\tCamera\t\tC <coordinates> <orientation> <fov>\n",
		STDERR_FILENO);
	ft_putstr_fd("\tLight\t\tL <coordinates> <brightness> <color>\n",
		STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd("\tSphere\t\tsp <coordinates> <diameter> <color>\n",
		STDERR_FILENO);
	ft_putstr_fd("\tPlane\t\tpl <coordinates> <normal> <color>\n",
		STDERR_FILENO);
	ft_putstr_fd("\tCylinder\tcy <coordinates> <axis> <diameter> <height> <color>\n",
		STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd("Made by hshimizu.\n", STDERR_FILENO);
	ft_putstr_fd("github\t: https://github.com/Neko-Sato\n", STDERR_FILENO);
	ft_putstr_fd("profile\t: https://profile.intra.42.fr/users/hshimizu\n",
		STDERR_FILENO);
}
